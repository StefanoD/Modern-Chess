#pragma once

#include "BitBoardConstants.h"
#include "Square.h"

namespace ModernChess::BitBoardOperations
{

    constexpr BitBoardState occupySquare(BitBoardState board, Square square)
    {
        const BitBoardState state = 1UL << square;
        board |= state;

        return board;
    }

    constexpr bool isOccupied(BitBoardState board, Square square)
    {
        const BitBoardState state = 1UL << square;
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
    constexpr BitBoardState mirrorHorizontal (BitBoardState board)
    {
        constexpr BitBoardState k1 = 0x5555555555555555;
        constexpr BitBoardState k2 = 0x3333333333333333;
        constexpr BitBoardState k4 = 0x0f0f0f0f0f0f0f0f;
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
    constexpr BitBoardState flipVertical(BitBoardState board)
    {
        constexpr BitBoardState k1 = 0x00FF00FF00FF00FF;
        constexpr BitBoardState k2 = 0x0000FFFF0000FFFF;
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
    constexpr BitBoardState rotate180(BitBoardState board)
    {
        return mirrorHorizontal(flipVertical(board));
    }

    constexpr int bitScanLookup[64] =
    {
            0, 47,  1, 56, 48, 27,  2, 60,
            57, 49, 41, 37, 28, 16,  3, 61,
            54, 58, 35, 52, 50, 42, 21, 44,
            38, 32, 29, 23, 17, 11,  4, 62,
            46, 55, 26, 59, 40, 36, 15, 53,
            34, 51, 20, 43, 31, 22, 10, 45,
            25, 39, 14, 33, 19, 30,  9, 24,
            13, 18,  8, 12,  7,  6,  5, 63
    };

    /**
     * bitScanForward
     * @author Kim Walisch (2012)
     * @param bitBoard bitboard to scan
     * @precondition bitBoard != 0
     * @see https://www.chessprogramming.org/BitScan
     * @return index (0..63) of least significant one bit
     */
    constexpr Square bitScanForward(BitBoardState bitBoard)
    {
        constexpr BitBoardState debruijn64 = 0x03f79d71b4cb0a89;
        //assert (bitBoard != 0);
        return Square(bitScanLookup[((bitBoard ^ (bitBoard - 1)) * debruijn64) >> 58]);
    }


    /**
     * bitScanReverse
     * @authors Kim Walisch, Mark Dickinson
     * @param bitBoard bitboard to scan
     * @precondition bitBoard != 0
     * @see https://www.chessprogramming.org/BitScan
     * @return index (0..63) of most significant one bit
     */
    Square bitScanReverse(BitBoardState bitBoard)
    {
        constexpr BitBoardState debruijn64 = 0x03f79d71b4cb0a89;
        //assert (bitBoard != 0);
        bitBoard |= bitBoard >> 1;
        bitBoard |= bitBoard >> 2;
        bitBoard |= bitBoard >> 4;
        bitBoard |= bitBoard >> 8;
        bitBoard |= bitBoard >> 16;
        bitBoard |= bitBoard >> 32;
        return Square(bitScanLookup[(bitBoard * debruijn64) >> 58]);
    }
}