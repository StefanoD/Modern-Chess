#include "ModernChess/Game.h"
#include "ModernChess/PseudoMoveGeneration.h"

using namespace ModernChess::MoveGenerations;

namespace ModernChess
{
    bool Game::makeMove(Move move, MoveType moveType)
    {
        if (gameState.board.sideToMove == Color::White)
        {
            return MoveExecution::executeMoveForWhite(gameState, move, moveType);
        }

        return MoveExecution::executeMoveForBlack(gameState, move, moveType);
    }

    std::vector<Move> Game::generateMoves() const
    {
        std::vector<Move> movesToBeGenerated;
        movesToBeGenerated.reserve(256);

        if (gameState.board.sideToMove == Color::White)
        {
            PseudoMoveGeneration::generateWhiteFigureMoves(gameState, movesToBeGenerated);
        }
        else
        {
            PseudoMoveGeneration::generateBlackFigureMoves(gameState, movesToBeGenerated);
        }

        return movesToBeGenerated;
    }
}


