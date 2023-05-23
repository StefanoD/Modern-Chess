#include "ModernChess/Game.h"
#include "ModernChess/PseudoMoveGeneration.h"

using namespace ModernChess::MoveGenerations;

namespace ModernChess
{
    bool Game::makeMove(Move move, MoveType moveType)
    {
        return MoveExecution::executeMove(gameState, move, moveType);
    }

    std::vector<Move> Game::generateMoves() const
    {
        return PseudoMoveGeneration::generateMoves(gameState);
    }
}


