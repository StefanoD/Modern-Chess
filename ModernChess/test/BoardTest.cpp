#include "ModernChess/BitBoard.h"

#include <gtest/gtest.h>

namespace
{
    using namespace ModernChess;

    BitBoardState getBitBoardConjunctions(const BitBoard &bitBoard)
    {
        return bitBoard.blackRookBitBoard & \
               bitBoard.blackKnightBitBoard & \
               bitBoard.blackBishopBitBoard & \
               bitBoard.blackQueenBitBoard & \
               bitBoard.blackKingBitBoard & \
               bitBoard.blackPawnBitBoard & \
               bitBoard.whiteRookBitBoard & \
               bitBoard.whiteKnightBitBoard & \
               bitBoard.whiteBishopBitBoard & \
               bitBoard.whiteQueenBitBoard & \
               bitBoard.whiteKingBitBoard & \
               bitBoard.whitePawnBitBoard;
    }

    TEST(Board, SquaresAreUniquelyOccupied)
    {
        BitBoard board;

        // This tests, that figures don't occupy the same square
        EXPECT_EQ(getBitBoardConjunctions(board).to_ulong(), 0U);

        const BitBoardState bitBoardState = board.getOccupiedSquares();

        // Test occupation of white figures
        for (int square = 0; square < 16; ++square)
        {
            EXPECT_TRUE(bitBoardState[square]);
        }

        // Test if squares are not occupied
        for (int square = 16; square < 48; ++square)
        {
            EXPECT_FALSE(bitBoardState[square]);
        }

        // Test occupation of black figures
        for (int square = 48; square < 64; ++square)
        {
            EXPECT_TRUE(bitBoardState[square]);
        }

        std::cout << board.printBitBoard(bitBoardState) << std::endl;
    }

    TEST(Board, BlackFiguresAreSet)
    {
        const BitBoard board;
        const BitBoardState bitBoardState = board.getBlackFigures();

        // Test if squares are not occupied
        for (int square = 0; square < 48; ++square)
        {
            EXPECT_FALSE(bitBoardState[square]);
        }

        // Test occupation of black figures
        for (int square = 48; square < 64; ++square)
        {
            EXPECT_TRUE(bitBoardState[square]);
        }

        std::cout << board.printBitBoard(bitBoardState) << std::endl;
    }

    TEST(Board, WhiteFiguresAreSet)
    {
        const BitBoard board;
        const BitBoardState bitBoardState = board.getWhiteFigures();

        // Test occupation of white figures
        for (int square = 0; square < 16; ++square)
        {
            EXPECT_TRUE(bitBoardState[square]);
        }

        // Test if squares are not occupied
        for (int square = 16; square < 64; ++square)
        {
            EXPECT_FALSE(bitBoardState[square]);
        }

        std::cout << board.printBitBoard(bitBoardState) << std::endl;
    }

    TEST(BitBoard, GetEmptySquares)
    {
        const BitBoard board;
        const BitBoardState occupiedSquares = board.getOccupiedSquares();
        const BitBoardState emptySquares = board.getEmptySquares();

        // Empty and occupied squares must be disjoint.
        // This can be tested with logical AND-operator and testing to 0.
        // See https://www.chessprogramming.org/General_Setwise_Operations
        EXPECT_EQ(occupiedSquares & emptySquares, 0);
    }
}


