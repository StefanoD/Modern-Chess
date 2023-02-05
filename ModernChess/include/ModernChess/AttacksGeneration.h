#pragma once

#include "BitBoardConstants.h"
#include "Square.h"

namespace ModernChess::AttacksGeneration
{
    // Attack calculations on an empty board.
    // See https://www.chessprogramming.org/On_an_empty_Board

    constexpr BitBoardState rankMask(Square square)
    {
        return  BitBoardConstants::firstRank << (square & 56);
    }

    constexpr BitBoardState fileMask(Square square)
    {
        return BitBoardConstants::aFile << (square & 7);
    }

    constexpr BitBoardState diagonalMask(Square square)
    {
        const int diagonal = 8 * (square & 7) - (square & 56);
        const int north = -diagonal & (diagonal >> 31);
        const int south = diagonal & (-diagonal >> 31);
        return (BitBoardConstants::a1H8Diagonal >> south) << north;
    }
}