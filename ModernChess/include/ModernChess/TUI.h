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
        static constexpr char getPromotedPiece(Figure figure)
        {
            switch (figure)
            {
                case Figure::WhiteQueen: return 'Q';
                case Figure::WhiteRook: return 'R';
                case Figure::WhiteBishop: return 'B';
                case Figure::WhiteKnight: return 'N';
                case Figure::BlackQueen: return 'q';
                case Figure::BlackRook: return 'r';
                case Figure::BlackBishop: return 'b';
                case Figure::BlackKnight: return 'n';
                default: throw std::invalid_argument("Figure type '" + std::to_string(figure) + "' cannot promote!");
            }
        }
    };
}