#pragma once

#include "GameState.h"

#include <vector>

namespace ModernChess {
    class Game
    {
    public:

    private:
        static std::array<std::array<BitBoardState, 64>, 2> pawnAttackTable;
        static std::array<BitBoardState, 64> knightAttackTable;
        static std::array<BitBoardState, 64> kingAttackTable;

        std::vector<GameState> m_gameHistory;
    };
}