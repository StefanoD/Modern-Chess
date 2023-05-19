#include "ModernChess/UCICommunication.h"
#include "ModernChess/UCIParser.h"

#include <cstdio>
#include <iostream>
#include <string>
#include <limits>

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
                // parse position
                continue;
            }
            
            if (parser.uiRequestsNewGame())
            {
                // call parse position function
                //parse_position("position startpos");
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
}