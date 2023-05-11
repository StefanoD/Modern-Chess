#pragma once

#include "BitBoardConstants.h"

#include <array>
#include <ostream>

namespace ModernChess
{
    class BitBoard
    {
    public:

        BitBoard();

        [[nodiscard]] BitBoardState getOccupiedSquares() const;
        [[nodiscard]] BitBoardState getEmptySquares() const;
        [[nodiscard]] BitBoardState getWhiteFigures() const;
        [[nodiscard]] BitBoardState getBlackFigures() const;

        // Every figure-type and every color has its own board representation
        std::array<BitBoardState, 12> bitboards{};
        // Occupancies for white, black and both colors
        std::array<BitBoardState, 3> occupancies{};
    };
}

std::ostream& operator<<(std::ostream& os, const ModernChess::BitBoard &bitBoard);