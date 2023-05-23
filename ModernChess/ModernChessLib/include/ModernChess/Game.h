#pragma once

#include "GameState.h"
#include "MoveExecution.h"

#include <vector>

namespace ModernChess {
    class Game
    {
    public:
        GameState gameState;

        bool makeMove(Move move, MoveType moveType);

        std::vector<Move> generateMoves() const;

    private:
        std::vector<GameState> m_gameHistory;
    };
}