#include "ModernChess/Game.h"
#include "ModernChess/PawnAttacks.h"
#include "ModernChess/KnightAttacks.h"
#include "ModernChess/KingAttacks.h"

namespace ModernChess
{
    const std::array<std::array<BitBoardState, 64>, 2> Game::pawnAttackTable = Attacks::generatePawnAttacks();
    const std::array<BitBoardState, 64> Game::knightAttackTable = Attacks::generateKnightAttacks();
    const std::array<BitBoardState, 64> Game::kingAttackTable = Attacks::generateKingAttacks();

    Game::Game() : queenAttacks(bishopAttacks, rookAttacks)
    {}

}