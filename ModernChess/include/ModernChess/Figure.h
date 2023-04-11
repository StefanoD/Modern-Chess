#pragma once

#include <cinttypes>

namespace ModernChess {

    enum FigureType : uint8_t
    {
        WhitePawn,
        WhiteKnight,
        WhiteBishop,
        WhiteRook,
        WhiteQueen,
        WhiteKing,
        BlackPawn,
        BlackKnight,
        BlackBishop,
        BlackRook,
        BlackQueen,
        BlackKing,
        None
    };

    // This makes it possible to use FigureType in for-loops
    inline FigureType &operator++(FigureType &state)
    {
        state = FigureType(uint8_t(state) + 1);
        return state;
    }

    inline FigureType &operator--(FigureType &state)
    {
        state = FigureType(uint8_t(state) - 1);
        return state;
    }
}