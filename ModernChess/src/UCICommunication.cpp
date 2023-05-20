#include "ModernChess/UCICommunication.h"
#include "ModernChess/UCIParser.h"
#include "ModernChess/FenParsing.h"

//#include <cstdio>
#include <iostream>
#include <string>
#include <limits>

using ModernChess::FenParsing::FenParser;

namespace ModernChess
{
    void UCICommunication::startCommunication()
    {
        // Disable buffered uiCommand and output for immediately feedback
        //std::setvbuf(stdin, nullptr, _IONBF, 0);
        //std::setvbuf(stdout, nullptr, _IONBF, 0);

        registerToUI();

        std::string uiCommand;

        for (getInput(uiCommand); ; getInput(uiCommand))
        {
            // make sure uiCommand is available
            if (uiCommand == "\n")
            {
                continue;
            }

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
            else if (parser.uiRequestsUCIMode())
            {
                registerToUI();
            }
        }
    }

    void UCICommunication::registerToUI()
    {
        std::cout << "id name Modern Chess\n"
                  << "id author Stefano Di Martino\n"
                  << "uciok\n" << std::flush;
    }

    void UCICommunication::sendAcknowledgeToUI()
    {
        std::cout << "readyok\n" << std::flush;
    }

    void UCICommunication::getInput(std::string &uiCommand)
    {
        std::cin >> uiCommand;

        // Flush the input stream
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    void UCICommunication::parsePosition(UCIParser &parser)
    {
        if (parser.uiHasSentStartingPosition())
        {
            createNewGame();
        }
        else if (parser.uiHasSentFENPosition())
        {
            const std::string_view fenString = parser.getNextString();
            m_game.gameState = FenParser(fenString).parse();
        }
        else
        {
            throw std::runtime_error("Missing position after position command: " +
                                      std::string(parser.currentStringView()));
        }

        if (parser.uiHasSentMoves())
        {
            const std::string_view moveCommand = parser.currentStringView();

            while (parser.hasNextCharacter())
            {
                const Move move = executeMoves(parser);

                if (not move.isNullMove())
                {
                    m_game.makeMove(move, MoveGenerations::MoveType::AllMoves);
                }
                else
                {
                    std::cerr << "Illegal move detected: " << moveCommand << std::endl;
                    break;
                }
            }
        }

        std::cout << m_game.gameState << std::endl;
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
        uint32_t searchDepth;

        if (parser.uiHasSentSearchDepth())
        {
            searchDepth = parser.parseNumber();
        }
        else
        {
            searchDepth = 6;
        }

        m_game.searchPosition(searchDepth);
    }
}