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
        int32_t halfMoveClock = 0;
        int32_t nextMoveClock = 0;


        //std::vector<Move> moveList;
    };

    bool operator==(const GameState&, const GameState&);
    bool operator!=(const GameState&, const GameState&);
}

std::ostream& operator<<(std::ostream& os, const ModernChess::GameState &gameState);