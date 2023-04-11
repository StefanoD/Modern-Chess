#include "ModernChess/AttackQueries.h"

#include "ModernChess/PawnAttacks.h"
#include "ModernChess/KnightAttacks.h"
#include "ModernChess/KingAttacks.h"

namespace ModernChess {
    const std::array<std::array<BitBoardState, 64>, 2> AttackQueries::pawnAttackTable = Attacks::generatePawnAttacks();
    const std::array<BitBoardState, 64> AttackQueries::knightAttackTable = Attacks::generateKnightAttacks();
    const std::array<BitBoardState, 64> AttackQueries::kingAttackTable = Attacks::generateKingAttacks();

    AttackQueries::AttackQueries() : queenAttacks(bishopAttacks, rookAttacks)
    {}
}