#pragma once

#include "GameState.h"

#include <vector>

namespace ModernChess {
    class Game
    {
    public:
        explicit Game(GameState gameState);
        

    private:
        GameState m_gameState;
        std::vector<GameState> m_gameHistory;
    };
}