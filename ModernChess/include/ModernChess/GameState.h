#pragma once

#include "BitBoard.h"
#include "Color.h"
#include "Square.h"
#include "CastlingRights.h"
#include "Move.h"

#include <vector>

namespace ModernChess
{
    class GameState
    {
    public:
        GameState();

    //private:
        BitBoard board{};
        // See https://www.chessprogramming.org/Halfmove_Clock
        uint32_t halfMoveClock = 0;
        uint32_t nextMoveClock = 0;
        Color sideToMove = Color::White;
        CastlingRights castleRights = CastlingRights::Undefined;
        Square enPassantTarget = Square::undefined;

        std::vector<Move> moveList;
    };
}

std::ostream& operator<<(std::ostream& os, const ModernChess::GameState &gameState);