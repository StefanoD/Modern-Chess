#pragma once

#include "BitBoard.h"
#include "Color.h"
#include "Square.h"

namespace ModernChess
{
    class GameState
    {
    public:

    private:
        BitBoard m_board{};
        // See https://www.chessprogramming.org/Halfmove_Clock
        uint32_t m_halfMoveClock = 0;
        Color m_sideToMove = Color::White;
        bool m_whiteHasCastleRights = true;
        bool m_blackHasCastleRights = true;
        Square enPassantTarget = Square::undefined;
    };
}