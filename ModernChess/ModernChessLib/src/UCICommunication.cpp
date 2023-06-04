#include "ModernChess/UCICommunication.h"
#include "ModernChess/UCIParser.h"
#include "ModernChess/FenParsing.h"
#include "ModernChess/Evaluation.h"

#include <string>

using ModernChess::FenParsing::FenParser;

namespace ModernChess
{
    UCICommunication::UCICommunication(std::istream &inputStream, std::ostream &outputStream, std::ostream &errorStream) :
            m_inputStream(inputStream),
            m_outputStream(outputStream),
            m_errorStream(errorStream)
    {}

    void UCICommunication::startCommunication()
    {
        registerToUI();

        std::string uiCommand;

        for (getInput(uiCommand); ;getInput(uiCommand))
        {
            // make sure uiCommand is available
            UCIParser parser(uiCommand);

            if (parser.uiQuitGame())
            {
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
                if (m_searchFinished)
                {
                    sendBestMove();
                }
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
        std::getline(m_inputStream, uiCommand);

        // Flush the input stream
        //m_inputStream.clear();
        //m_inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
            m_game.gameState = fenParser.parse();

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
        m_game.gameState = FenParser(FenParsing::startPosition).parse();
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
        int32_t searchDepth;

        {
            const std::lock_guard lock(m_mutex);
            m_searchFinished = false;
        }

        if (parser.uiHasSentSearchDepth())
        {
            searchDepth = parser.parseNumber<int32_t>();
        }
        else
        {
            searchDepth = 7;
        }

        searchBestMove(searchDepth);
    }

    void UCICommunication::searchBestMove(int32_t searchDepth)
    {
        Evaluation evaluation(m_game.gameState);

        EvaluationResult evalResult;

        for (int currentDepth = 1; currentDepth <= searchDepth; ++currentDepth)
        {
            evalResult = evaluation.getBestMove(currentDepth);

            m_outputStream << evalResult << std::flush;
        }

        setBestMove(evalResult.bestMove());
        sendBestMove();
    }

    void UCICommunication::setBestMove(Move move)
    {
        const std::lock_guard lock(m_mutex);
        m_searchFinished = true;
        m_bestMove = move;
    }

    void UCICommunication::sendBestMove()
    {
        const Move bestMove = getBestMove();
        m_outputStream << "bestmove " << bestMove << "\n" << std::flush;
    }

    Move UCICommunication::getBestMove() const
    {
        const std::unique_lock lock(m_mutex);
        return m_bestMove;
    }
}