#pragma once

#include "GameState.h"
#include "SlidingPieceAttackGeneration.h"

#include <vector>

namespace ModernChess {
    class Game
    {
    public:

    private:
        static std::array<std::array<BitBoardState, 64>, 2> pawnAttackTable;
        static std::array<BitBoardState, 64> knightAttackTable;
        static std::array<BitBoardState, 64> kingAttackTable;
        static AttackGeneration::SlidingPieces::BishopAttacks bishopAttacks;
        static AttackGeneration::SlidingPieces::RookAttacks rookAttacks;

        std::vector<GameState> m_gameHistory;
    };
}