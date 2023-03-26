#pragma once

#include "GameState.h"
#include "PawnAttackGeneration.h"

#include <vector>

namespace ModernChess {
    class Game
    {
    public:

    private:
        static std::array<std::array<BitBoardState, 64>, 2> pawnAttackTable;

        std::vector<GameState> m_gameHistory;
    };
}