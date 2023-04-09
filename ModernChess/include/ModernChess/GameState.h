#pragma once

#include "BitBoard.h"
#include "Color.h"
#include "Square.h"

namespace ModernChess
{

    /**
       binary | decimal

       0001     1  white king can castle to the king side
       0010     2  white king can castle to the queen side
       0100     4  black king can castle to the king side
       1000     8  black king can castle to the queen side
       examples
       1111       both sides can castle both directions
       1001       black king => queen side
                  white king => king side
    */

    enum CastleRights
    {
        WhiteKingSide = 1,
        WhiteQueenSide = 2,
        BlackKindSide = 4,
        BlackQueenSide = 8
    };

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