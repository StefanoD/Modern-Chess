#pragma once

#include "GameState.h"

#include <vector>

namespace ModernChess {
    class Game
    {
    public:

    private:
        std::vector<GameState> m_gameStates;
    };
}