#pragma once

#include "Square.h"

#include <ostream>

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
    enum CastleRights : uint8_t
    {
        Undefined = 0,
        WhiteKingSide = 1,
        WhiteQueenSide = 2,
        WhiteAnySide = WhiteKingSide + WhiteQueenSide,
        BlackKingSide = 4,
        BlackQueenSide = 8,
        BlackAnySide = BlackKingSide + BlackQueenSide
    };

    namespace Details
    {
        /*
         * For updating castle right in an efficient way when a piece has moved
         *                              castling    move     in      in
         *                              right       update   binary  decimal
         *   king & rooks didn't move:  1111    &   1111  =  1111    15
         *          white king  moved:  1111    &   1100  =  1100    12
         *    white king's rook moved:  1111    &   1110  =  1110    14
         *   white queen's rook moved:  1111    &   1101  =  1101    13
         *
         *           black king moved:  1111    &   0011  =  1011    3
         *    black king's rook moved:  1111    &   1011  =  1011    11
         *   black queen's rook moved:  1111    &   0111  =  0111    7
        */

        // castling rights update constants
        constexpr std::array<uint8_t, 64> castlingRightsLookUpTable {
                13, 15, 15, 15, 12, 15, 15, 14,
                15, 15, 15, 15, 15, 15, 15, 15,
                15, 15, 15, 15, 15, 15, 15, 15,
                15, 15, 15, 15, 15, 15, 15, 15,
                15, 15, 15, 15, 15, 15, 15, 15,
                15, 15, 15, 15, 15, 15, 15, 15,
                15, 15, 15, 15, 15, 15, 15, 15,
                7, 15, 15, 15,  3, 15, 15, 11
        };
    }

    constexpr bool whiteCanCastleKingSide(CastleRights castleRights)
    {
        return (castleRights & CastleRights::WhiteKingSide) == CastleRights::WhiteKingSide;
    }

    constexpr bool whiteCanCastleQueenSide(CastleRights castleRights)
    {
        return (castleRights & CastleRights::WhiteQueenSide) == CastleRights::WhiteQueenSide;
    }

    constexpr bool blackCanCastleKingSide(CastleRights castleRights)
    {
        return (castleRights & CastleRights::BlackKingSide) == CastleRights::BlackKingSide;
    }

    constexpr bool blackCanCastleQueenSide(CastleRights castleRights)
    {
        return (castleRights & CastleRights::BlackQueenSide) == CastleRights::BlackQueenSide;
    }

    constexpr CastleRights addWhiteKingSideCastleRights(CastleRights castleRights)
    {
        return CastleRights(castleRights | CastleRights::WhiteKingSide);
    }

    constexpr CastleRights addWhiteQueenSideCastleRights(CastleRights castleRights)
    {
        return CastleRights(castleRights | CastleRights::WhiteQueenSide);
    }

    constexpr CastleRights addBlackKingSideCastleRights(CastleRights castleRights)
    {
        return CastleRights(castleRights | CastleRights::BlackKingSide);
    }

    constexpr CastleRights addBlackQueenSideCastleRights(CastleRights castleRights)
    {
        return CastleRights(castleRights | CastleRights::BlackQueenSide);
    }

    constexpr CastleRights updateCastleRights(CastleRights castleRights, Square movedFrom, Square movedTo)
    {
        return CastleRights(castleRights &
                            Details::castlingRightsLookUpTable[movedFrom] &
                            Details::castlingRightsLookUpTable[movedTo]);
    }
}

std::ostream& operator<<(std::ostream& os, ModernChess::CastleRights castleRights);