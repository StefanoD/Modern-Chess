#pragma once

#include "ModernChess/Figure.h"

#include <stdexcept>
#include <string>

namespace ModernChess {
    /**
     * @brief Terminal User Interface
     */
    class TUI
    {
    public:
        static constexpr std::array<char, Figure::None> promotedPieceToCharacter = [] {
            std::array<char, Figure::None> a{};
            a[Figure::WhiteKnight] = 'N';
            a[Figure::WhiteBishop] = 'B';
            a[Figure::WhiteRook] = 'R';
            a[Figure::WhiteQueen] = 'Q';
            a[Figure::BlackKnight] = 'n';
            a[Figure::BlackBishop] = 'b';
            a[Figure::BlackRook] = 'r';
            a[Figure::BlackQueen] = 'q';
            return a;
        } ();
    };
}