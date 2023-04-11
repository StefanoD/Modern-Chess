#pragma once

#include "GameState.h"
#include "QueenAttacks.h"

#include <vector>

namespace ModernChess {
    class Game
    {
    public:

        Game();

    private:
        static const std::array<std::array<BitBoardState, 64>, 2> pawnAttackTable;
        static const std::array<BitBoardState, 64> knightAttackTable;
        static const std::array<BitBoardState, 64> kingAttackTable;
        static const BishopAttacks bishopAttacks;
        static const RookAttacks rookAttacks;
        QueenAttacks queenAttacks;

        std::vector<GameState> m_gameHistory;
    };
}