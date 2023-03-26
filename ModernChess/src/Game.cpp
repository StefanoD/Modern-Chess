#include "ModernChess/Game.h"

namespace ModernChess
{
    std::array<std::array<BitBoardState, 64>, 2> Game::pawnAttackTable = AttackGeneration::generatePawnAttacks();
}