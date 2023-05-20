#pragma once

#include "GameState.h"
#include "MoveExecution.h"

#include <vector>

namespace ModernChess {
    class Game
    {
    public:
        GameState gameState;

        bool makeMove(Move move, MoveGenerations::MoveType moveType);

        std::vector<Move> generateMoves() const;

        void searchPosition(uint32_t depth);

    private:
        std::vector<GameState> m_gameHistory;
    };
}