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

            if (parser.uiHasSentFENPosition())
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
                // call parse position function
                // parse_go(input);
            }
            else if (parser.uiRequestsUCIMode())
            {
                registerToUI();
            }

            // Flush answer to UI
            std::cout << std::flush;
        }
    }

    void UCICommunication::registerToUI()
    {
        std::cout << "id name Modern Chess\n";
        std::cout << "id author Stefano Di Martino\n";
        std::cout << "uciok\n" << std::flush;
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
        if (parser.uiHasSentFENPosition())
        {
            const std::string_view fenString = parser.getNextString();
            m_game.gameState = FenParser(fenString).parse();
        }
    }

    void UCICommunication::createNewGame()
    {
        m_game.gameState = FenParser(FenParsing::startPosition).parse();
    }
}