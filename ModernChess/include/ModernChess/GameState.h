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
        BitBoard m_board{};
        // See https://www.chessprogramming.org/Halfmove_Clock
        uint32_t m_halfMoveClock = 0;
        Color m_sideToMove = Color::White;
        CastleRights castleRights{};
        Square m_enPassantTarget = Square::undefined;
    };
}

std::ostream& operator<<(std::ostream& os, const ModernChess::GameState &gameState);