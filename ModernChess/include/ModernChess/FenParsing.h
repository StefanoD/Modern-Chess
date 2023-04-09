#pragma once

#include "Figure.h"

#include <array>
#include <string_view>
#include <string>

namespace ModernChess {
    // See https://de.wikipedia.org/wiki/Forsyth-Edwards-Notation

    // ASCII pieces
    constexpr auto asciiFigures = "PNBRQKpnbrqk";

    // unicode pieces
    constexpr std::array<std::string_view, 12> unicodeFigures {"♙", "♘", "♗", "♖", "♕", "♔", "♟︎", "♞", "♝", "♜", "♛", "♚"};

    constexpr ColoredFigureTypes charToEnum(char fenChar)
    {
        switch (fenChar)
        {
            case 'P': return ColoredFigureTypes::WhitePawn;
            case 'N': return ColoredFigureTypes::WhiteKnight;
            case 'B': return ColoredFigureTypes::WhiteBishop;
            case 'R': return ColoredFigureTypes::WhiteRook;
            case 'Q': return ColoredFigureTypes::WhiteQueen;
            case 'K': return ColoredFigureTypes::WhiteKing;
            case 'p': return ColoredFigureTypes::BlackPawn;
            case 'n': return ColoredFigureTypes::BlackKnight;
            case 'b': return ColoredFigureTypes::BlackBishop;
            case 'r': return ColoredFigureTypes::BlackRook;
            case 'q': return ColoredFigureTypes::BlackQueen;
            case 'k': return ColoredFigureTypes::BlackKing;
            default: throw std::range_error("Could not parse FEN character '" + std::string(1, fenChar) + "' to Figure");
        }
    }
}