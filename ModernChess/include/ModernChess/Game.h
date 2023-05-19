#pragma once

#include "GameState.h"

#include <vector>

namespace ModernChess {
    class Game
    {
    public:
        GameState gameState;

    private:
        std::vector<GameState> m_gameHistory;
    };
}