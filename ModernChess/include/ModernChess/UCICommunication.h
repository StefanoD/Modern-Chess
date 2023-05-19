#pragma once

#include "Game.h"

#include <string>

namespace ModernChess
{
    class UCIParser;

    class UCICommunication
    {
    public:
        void startCommunication();

    private:
        Game m_game;

        static void registerToUI();

        static void sendAcknowledgeToUI();

        static void getInput(std::string &uiCommand);

        void parsePosition(UCIParser &parser);

        void createNewGame();
    };
}