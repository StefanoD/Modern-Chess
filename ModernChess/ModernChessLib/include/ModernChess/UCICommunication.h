#pragma once

#include "Game.h"

#include <string>
#include <istream>
#include <ostream>

namespace ModernChess
{
    class UCIParser;

    class UCICommunication
    {
    public:
        explicit UCICommunication(std::istream &inputStream, std::ostream &outputStream, std::ostream &errorStream);

        void startCommunication();

        [[nodiscard]] GameState getGameState() const { return m_game.gameState; }

    private:
        Game m_game;
        std::istream &m_inputStream;
        std::ostream &m_outputStream;
        std::ostream &m_errorStream;

        void registerToUI();

        void sendAcknowledgeToUI();

        void getInput(std::string &uiCommand);

        void parsePosition(UCIParser &parser);

        Move executeMoves(UCIParser &parser);

        void executeGoCommand(UCIParser &parser);

        void createNewGame();

        void sendBestMove(int32_t searchDepth);
    };
}