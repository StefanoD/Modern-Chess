#pragma once

#include <cinttypes>

namespace ModernChess {
    enum class FigureType
    {
        Pawn,
        Bishop,
        Knight,
        Rook,
        Queen,
        King
    };

    enum ColoredFigureType : uint8_t
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

    // This makes it possible to use ColoredFigureType in for-loops
    inline ColoredFigureType& operator++(ColoredFigureType& state)
    {
        state = ColoredFigureType(uint8_t(state) + 1);
        return state;
    }

    inline ColoredFigureType& operator--(ColoredFigureType& state)
    {
        state = ColoredFigureType(uint8_t(state) - 1);
        return state;
    }
}