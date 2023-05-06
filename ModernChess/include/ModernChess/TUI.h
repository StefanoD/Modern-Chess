#pragma once

#include "ModernChess/Figure.h"

#include <array>

namespace ModernChess {
    /**
     * @brief Terminal User Interface
     */
    class TUI
    {
    public:
        /**
         * @brief UCI compliant promotion encoding
         */
        static constexpr std::array<char, 255> promotedPieceToCharacter = [] {
            std::array<char, 255> a = {};
            a[Figure::WhiteKnight] = 'n';
            a[Figure::WhiteBishop] = 'b';
            a[Figure::WhiteRook] = 'r';
            a[Figure::WhiteQueen] = 'q';
            a[Figure::BlackKnight] = 'n';
            a[Figure::BlackBishop] = 'b';
            a[Figure::BlackRook] = 'r';
            a[Figure::BlackQueen] = 'q';
            return a;
        } ();
    };
}