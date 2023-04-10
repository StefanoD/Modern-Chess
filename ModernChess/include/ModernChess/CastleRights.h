#pragma once

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

    constexpr bool whiteCanKingSideCastle(CastleRights castleRights)
    {
        return (castleRights & CastleRights::WhiteKingSide) == CastleRights::WhiteKingSide;
    }

    constexpr bool whiteCanQueenSideCastle(CastleRights castleRights)
    {
        return (castleRights & CastleRights::WhiteQueenSide) == CastleRights::WhiteQueenSide;
    }

    constexpr bool blackCanKingSideCastle(CastleRights castleRights)
    {
        return (castleRights & CastleRights::BlackKingSide) == CastleRights::BlackKingSide;
    }

    constexpr bool blackCanQueenSideCastle(CastleRights castleRights)
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
}

std::ostream& operator<<(std::ostream& os, ModernChess::CastleRights castleRights);