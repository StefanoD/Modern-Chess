#include "ModernChess/Game.h"
#include "ModernChess/PawnAttackGeneration.h"
#include "ModernChess/KnightAttackGeneration.h"
#include "ModernChess/KingAttackGeneration.h"

namespace ModernChess
{
    std::array<std::array<BitBoardState, 64>, 2> Game::pawnAttackTable = AttackGeneration::generatePawnAttacks();
    std::array<BitBoardState, 64> Game::knightAttackTable = AttackGeneration::generateKnightAttacks();
    std::array<BitBoardState, 64> Game::kingAttackTable = AttackGeneration::generateKingAttacks();

    Game::Game() : queenAttacks(bishopAttacks, rookAttacks)
    {}

}