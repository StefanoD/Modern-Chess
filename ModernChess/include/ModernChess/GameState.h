#pragma once

#include "BitBoard.h"
#include "Color.h"
#include "Square.h"
#include "CastleRights.h"

namespace ModernChess
{
    class GameState
    {
    public:

    //private:
        BitBoard board{};
        // See https://www.chessprogramming.org/Halfmove_Clock
        uint32_t halfMoveClock = 0;
        Color sideToMove = Color::White;
        CastleRights castleRights{};
        Square enPassantTarget = Square::undefined;
    };
}

std::ostream& operator<<(std::ostream& os, const ModernChess::GameState &gameState);