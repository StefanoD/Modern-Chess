#pragma once

#include "Board.h"
#include "Move.h"

#include <vector>

namespace ModernChess
{
    class GameState
    {
    public:
        GameState();

    //private:
        Board board{};
        // See https://www.chessprogramming.org/Halfmove_Clock
        uint32_t halfMoveClock = 0;
        uint32_t nextMoveClock = 0;

        //std::vector<Move> moveList;
    };
}

std::ostream& operator<<(std::ostream& os, const ModernChess::GameState &gameState);