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

    enum ColoredFigureTypes
    {
        WhitePawn, WhiteKnight, WhiteBishop, WhiteRook, WhiteQueen, WhiteKing,
        BlackPawn, BlackKnight, BlackBishop, BlackRook, BlackQueen, BlackKing
    };
}