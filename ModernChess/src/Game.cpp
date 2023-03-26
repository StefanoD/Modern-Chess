#include "ModernChess/Game.h"
#include "ModernChess/PawnAttackGeneration.h"
#include "ModernChess/KnightAttackGeneration.h"

namespace ModernChess
{
    std::array<std::array<BitBoardState, 64>, 2> Game::pawnAttackTable = AttackGeneration::generatePawnAttacks();
    std::array<BitBoardState, 64> Game::knightAttackTable = AttackGeneration::generateKnightAttacks();
}