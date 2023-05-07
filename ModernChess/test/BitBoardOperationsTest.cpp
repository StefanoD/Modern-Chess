#include "ModernChess/BitBoardOperations.h"
#include "ModernChess/RookAttacks.h"
#include "ModernChess/Utilities.h"

#include <gtest/gtest.h>

namespace
{
    using namespace ModernChess;

    TEST(BitBoardOperationsTest, occupyAndEraseSquare)
    {
        BitBoardState bitBoardState = BoardState::empty;
        bitBoardState = BitBoardOperations::occupySquare(bitBoardState, Square::a1);
        EXPECT_TRUE(BitBoardOperations::isOccupied(bitBoardState, Square::a1));
        EXPECT_NE(bitBoardState, 0);

        bitBoardState = BitBoardOperations::eraseSquare(bitBoardState, Square::a1);
        EXPECT_FALSE(BitBoardOperations::isOccupied(bitBoardState, Square::a1));
        EXPECT_EQ(bitBoardState, 0);
    }

    TEST(BitBoardOperationsTest, bitScanForward)
    {
        BitBoardState bitBoardState = BoardState::empty;
        bitBoardState = BitBoardOperations::occupySquare(bitBoardState, Square::a1);
        bitBoardState = BitBoardOperations::occupySquare(bitBoardState, Square::a2);

        const Square square = BitBoardOperations::bitScanForward(bitBoardState);
        EXPECT_EQ(square, Square::a1);
    }

    TEST(BitBoardOperationsTest, bitScanReverse)
    {
        BitBoardState bitBoardState = BoardState::empty;
        bitBoardState = BitBoardOperations::occupySquare(bitBoardState, Square::a1);
        bitBoardState = BitBoardOperations::occupySquare(bitBoardState, Square::a2);

        const Square square = BitBoardOperations::bitScanReverse(bitBoardState);
        EXPECT_EQ(square, Square::a2);
    }

    TEST(BitBoardOperationsTest, countBits)
    {
        BitBoardState bitBoardState = BoardState::empty;
        EXPECT_EQ(BitBoardOperations::countBits(bitBoardState), 0);
        bitBoardState = BitBoardOperations::occupySquare(bitBoardState, Square::a1);
        EXPECT_EQ(BitBoardOperations::countBits(bitBoardState), 1);
        bitBoardState = BitBoardOperations::occupySquare(bitBoardState, Square::a2);
        EXPECT_EQ(BitBoardOperations::countBits(bitBoardState), 2);
    }

    TEST(BitBoardOperationsTest, setOccupancy)
    {
        const BitBoardState attackMask = RookAttackHelperFunctions::maskRookAttacks(Square::a1);
        const uint32_t numberBits = BitBoardOperations::countBits(attackMask);
        const uint32_t magicNumber = 4095;
        const BitBoardState board = BitBoardOperations::setOccupancy(magicNumber, numberBits, attackMask);

        const std::vector<Square> expectedOccupiedSquares{
                b1, c1, d1, e1, f1, g1,
                a2,
                a3,
                a4,
                a5,
                a6,
                a7,
        };

        const std::vector<Square> expectedEmptySquares{
                a1,                         h1,
                b2, c2, d2, e2, f2, g2, h2,
                b3, c3, d3, e3, f3, g3, h3,
                b4, c4, d4, e4, f4, g4, h4,
                b5, c5, d5, e5, f5, g5, h5,
                b6, c6, d6, e6, f6, g6, h6,
                b7, c7, d7, e7, f7, g7, h7,
                a8, b8, c8, d8, e8, f8, g8, h8,
        };

        for (const Square square: expectedOccupiedSquares)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(board, square));
        }

        for (const Square square: expectedEmptySquares)
        {
            EXPECT_FALSE(BitBoardOperations::isOccupied(board, square));
        }

        print(std::cout, board) << std::endl;
    }

    TEST(BitBoardOperationsTest, getSquare)
    {
        EXPECT_EQ(Square::a1,  BitBoardOperations::getSquare(0, 0));
        EXPECT_EQ(Square::f5,  BitBoardOperations::getSquare(4, 5));
    }
}