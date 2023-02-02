#pragma once

#include "BitBoardConstants.h"
#include "Square.h"

namespace ModernChess::BitboardOperations
{

    static constexpr BitBoardState oneStepNorth(BitBoardState state)
    {
        return state << 8;
    }

    static constexpr BitBoardState oneStepSouth(BitBoardState state)
    {
        return state >> 8;
    }

    static constexpr BitBoardState occupySquare(BitBoardState board, Square square)
    {
        const uint64_t state = 1UL << square;
        board |= state;

        return board;
    }

    static constexpr bool isOccupied(BitBoardState board, Square square)
    {
        const uint64_t state = 1UL << square;
        board &= state;

        return board == state;
    }

    /**
     * @brief Mirror a bitboard horizontally about the center files.
     *        File a is mapped to file h and vice versa.
     * @param board any bitboard
     * @see https://www.chessprogramming.org/Flipping_Mirroring_and_Rotating
     * @return bitboard board mirrored horizontally
     */
    static constexpr BitBoardState mirrorHorizontal (BitBoardState board)
    {
        constexpr uint64_t k1 = 0x5555555555555555;
        constexpr uint64_t k2 = 0x3333333333333333;
        constexpr uint64_t k4 = 0x0f0f0f0f0f0f0f0f;
        board = ((board >> 1) & k1) + 2 * (board & k1);
        board = ((board >> 2) & k2) + 4 * (board & k2);
        board = ((board >> 4) & k4) + 16 * (board & k4);
        return board;
    }

    /**
     * @brief Flip a bitboard vertically about the centre ranks.
     *        Rank 1 is mapped to rank 8 and vice versa.
     * @param board any bitboard
     * @see https://www.chessprogramming.org/Flipping_Mirroring_and_Rotating
     * @return bitboard board flipped vertically
     */
    static constexpr BitBoardState flipVertical(BitBoardState board)
    {
        constexpr uint64_t k1 = 0x00FF00FF00FF00FF;
        constexpr uint64_t k2 = 0x0000FFFF0000FFFF;
        board = ((board >> 8) & k1) | ((board & k1) << 8);
        board = ((board >> 16) & k2) | ((board & k2) << 16);
        board = ( board >> 32) | ( board << 32);
        return board;
    }

    /**
     * Rotate a bitboard by 180 degrees.
     * Square a1 is mapped to h8, and a8 is mapped to h1.
     * @param board any bitboard
     * @see https://www.chessprogramming.org/Flipping_Mirroring_and_Rotating
     * @return bitboard board rotated 180 degrees
     */
    static constexpr BitBoardState rotate180(BitBoardState board)
    {
        return mirrorHorizontal(flipVertical(board));
    }
}