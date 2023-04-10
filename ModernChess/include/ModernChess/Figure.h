#pragma once

#include <cinttypes>

namespace ModernChess {
    enum class FigureTypes
    {
        Pawn,
        Bishop,
        Knight,
        Rook,
        Queen,
        King
    };

    enum ColoredFigureTypes : uint8_t
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

    // This makes it possible to use ColoredFigureTypes in for-loops
    inline ColoredFigureTypes& operator++(ColoredFigureTypes& state)
    {
        state = ColoredFigureTypes(uint8_t(state)+1);
        return state;
    }

    inline ColoredFigureTypes& operator--(ColoredFigureTypes& state)
    {
        state = ColoredFigureTypes(uint8_t(state)-1);
        return state;
    }
}