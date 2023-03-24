#include "ModernChess/BitBoardOperations.h"

#include <gtest/gtest.h>

namespace
{
    using namespace ModernChess;

    TEST(BitBoardOperationsTest, occupyAndEraseSquare)
    {
        BitBoardState bitBoardState = 0;
        bitBoardState = BitBoardOperations::occupySquare(bitBoardState, Square::a1);
        EXPECT_TRUE(BitBoardOperations::isOccupied(bitBoardState, Square::a1));
        EXPECT_NE(bitBoardState, 0);

        bitBoardState = BitBoardOperations::eraseSquare(bitBoardState, Square::a1);
        EXPECT_FALSE(BitBoardOperations::isOccupied(bitBoardState, Square::a1));
        EXPECT_EQ(bitBoardState, 0);
    }

    TEST(BitBoardOperationsTest, bitScanForward)
    {
        BitBoardState bitBoardState = 0;
        bitBoardState = BitBoardOperations::occupySquare(bitBoardState, Square::a1);
        bitBoardState = BitBoardOperations::occupySquare(bitBoardState, Square::a2);

        const Square square = BitBoardOperations::bitScanForward(bitBoardState);
        EXPECT_EQ(square, Square::a1);
    }

    TEST(BitBoardOperationsTest, bitScanReverse)
    {
        BitBoardState bitBoardState = 0;
        bitBoardState = BitBoardOperations::occupySquare(bitBoardState, Square::a1);
        bitBoardState = BitBoardOperations::occupySquare(bitBoardState, Square::a2);

        const Square square = BitBoardOperations::bitScanReverse(bitBoardState);
        EXPECT_EQ(square, Square::a2);
    }

}