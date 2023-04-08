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

    ///< FEN notation to ColoredFigureTypes
    enum ColoredFigureTypes : uint8_t
    {
        WhitePawn = 'P',
        WhiteKnight = 'N',
        WhiteBishop = 'B',
        WhiteRook = 'R',
        WhiteQueen = 'Q',
        WhiteKing = 'K',
        BlackPawn = 'p',
        BlackKnight = 'n',
        BlackBishop = 'b',
        BlackRook = 'r',
        BlackQueen = 'q',
        BlackKing = 'k',
        UndefinedColoredFigure
    };
}