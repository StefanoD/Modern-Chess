#pragma once

#include "Board.h"
#include "Move.h"
#include "ZobristHasher.h"

namespace ModernChess
{
    class GameState
    {
    public:
        GameState() = default;

    //private:
        Board board{};
        // See https://www.chessprogramming.org/Halfmove_Clock
        int32_t halfMoveClock = 0;
        int32_t nextMoveClock = 0;
        uint64_t gameStateHash = 0;


        //std::vector<Move> moveList;
        bool operator==(const GameState &other) const = default;

    private:
        static const ZobristHasher hasher;
    };

}

std::ostream& operator<<(std::ostream& os, const ModernChess::GameState &gameState);