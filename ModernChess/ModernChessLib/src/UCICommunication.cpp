#include "ModernChess/UCICommunication.h"
#include "ModernChess/UCIParser.h"
#include "ModernChess/FenParsing.h"
#include "ModernChess/Evaluation.h"

#include <string>

using ModernChess::FenParsing::FenParser;
using namespace std::chrono_literals;

namespace ModernChess
{
    UCICommunication::UCICommunication(std::istream &inputStream, std::ostream &outputStream, std::ostream &errorStream) :
            m_inputStream(inputStream),
            m_outputStream(outputStream),
            m_errorStream(errorStream),
            m_timeToSearch(std::numeric_limits<int64_t>::max()),
            m_searchThread(&UCICommunication::searchBestMove, this)
    {}

    UCICommunication::~UCICommunication()
    {
        quitGame();

        if (m_searchThread.joinable())
        {
            m_searchThread.join();
        }
    }

    void UCICommunication::startCommunication()
    {
        registerToUI();

        std::string uiCommand;

        for (getInput(uiCommand); ;getInput(uiCommand))
        {
            if (uiCommand.empty())
            {
                continue;
            }
            // make sure uiCommand is available
            UCIParser parser(uiCommand);

            if (parser.uiQuitGame())
            {
                quitGame();
                break;
            }

            if (parser.uiIsReady())
            {
                sendAcknowledgeToUI();
                continue;
            }

            if (parser.uiHasSentPosition())
            {
                parsePosition(parser);
                continue;
            }

            if (parser.uiRequestsNewGame())
            {
                createNewGame();
            }
            else if (parser.uiHasSentGoCommand())
            {
                executeGoCommand(parser);
            }
            else if (parser.uiHasSentStopCommand())
            {
                stopSearch();
                m_waitForSearchRequest.notifyOne();
            }
            else if (parser.uiRequestsUCIMode())
            {
                registerToUI();
            }
            else
            {
                m_errorStream << "Unknown command: " << parser.currentStringView() << std::endl << std::flush;
            }
        }
    }

    void UCICommunication::registerToUI()
    {
        m_outputStream << "id name Modern Chess\n"
                       << "id author Stefano Di Martino\n"
                       << "uciok\n" << std::flush;
    }

    void UCICommunication::sendAcknowledgeToUI()
    {
        m_outputStream << "readyok\n" << std::flush;
    }

    void UCICommunication::getInput(std::string &uiCommand)
    {
        m_inputStream.clear(); // Clear errors
        std::getline(m_inputStream, uiCommand);
    }

    void UCICommunication::parsePosition(UCIParser &parser)
    {
        if (parser.uiHasSentStartingPosition())
        {
            createNewGame();
        }
        else if (parser.uiHasSentFENPosition())
        {
            FenParser fenParser(parser.currentStringView());
            setGameState(fenParser.parse());

            // There might be consecutive move commands. So continue with parsing...
            parser = UCIParser(fenParser.currentStringView());
        }
        else
        {
            throw std::runtime_error("Missing position after position command: " +
                                      std::string(parser.completeStringView()));
        }

        if (parser.uiHasSentMoves())
        {
            const std::string_view moveCommand = parser.currentStringView();
            const std::lock_guard lock(m_mutex); // Add mutex for game state change

            while (parser.hasNextCharacter())
            {
                const Move move = executeMoves(parser);

                if (not move.isNullMove())
                {
                    m_game.makeMove(move, MoveType::AllMoves);
                }
                else
                {
                    m_errorStream << "Illegal move detected: " << moveCommand << std::endl;
                    break;
                }
            }
        }
    }

    void UCICommunication::createNewGame()
    {
        setGameState(FenParser(FenParsing::startPosition).parse());
    }

    Move UCICommunication::executeMoves(UCIParser &parser)
    {
        const UCIParser::UCIMove uciMove = parser.parseMove();
        const std::vector<Move> possibleMovesFromCurrentSate = m_game.generateMoves();

        for (const Move move : possibleMovesFromCurrentSate)
        {
            if (move.getFrom() == uciMove.sourceSquare and
                move.getTo() == uciMove.targetSquare)
            {
                if (const Figure promotedPiece = move.getPromotedPiece();
                        promotedPiece != Figure::None)
                {
                    if (uciMove.legalPromotionCharacter)
                    {
                        return move;
                    }
                    // Illegal Move --> Return Null Move
                    return {};
                }
                return move;
            }
        }

        // Illegal Move --> Return Null Move
        return {};
    }

    void UCICommunication::executeGoCommand(UCIParser &parser)
    {
        int32_t depth;

        if (parser.uiHasSentSearchDepth())
        {
            depth = parser.parseNumber<int32_t>();
        }
        else
        {
            depth = 13;
        }

        {
            const std::lock_guard lock(m_mutex);
            m_stopped = false;
            searchRequest.timeToSearch = std::chrono::milliseconds(std::numeric_limits<int64_t>::max());
            searchRequest.depth = depth;
        }

        m_waitForSearchRequest.notifyOne();
    }

    void UCICommunication::searchBestMove()
    {
        while (not gameHasBeenQuit())
        {
            {
                std::unique_lock lock(m_mutex);
                m_waitForSearchRequest.wait(lock, [this]{
                    return (not m_stopped) or m_quit;
                });
            }

            Evaluation evaluation(getGameState());
            EvaluationResult evalResult;

            for (int currentDepth = 1; currentDepth <= searchRequest.depth && (not searchHasBeenStopped()); ++currentDepth)
            {
                evalResult = evaluation.getBestMove(currentDepth);

                m_outputStream << evalResult << std::flush;
            }

            if (evalResult.pvTable != nullptr)
            {
                m_outputStream << "bestmove " << evalResult.bestMove() << "\n" << std::flush;
            }

            stopSearch();
        }
    }

    void UCICommunication::stopSearch()
    {
        const std::lock_guard lock(m_mutex);
        m_stopped = true;
    }

    void UCICommunication::quitGame()
    {
        {
            const std::lock_guard lock(m_mutex);
            m_stopped = true;
            m_quit = true;
        }
        m_waitForSearchRequest.notifyOne();
    }

    bool UCICommunication::searchHasBeenStopped() const
    {
        const std::lock_guard lock(m_mutex);
        return m_stopped;
    }

    bool UCICommunication::gameHasBeenQuit() const
    {
        const std::lock_guard lock(m_mutex);
        return m_quit;
    }

    void UCICommunication::setGameState(GameState getGameState)
    {
        const std::lock_guard lock(m_mutex);
        m_game.gameState = getGameState;
    }
}