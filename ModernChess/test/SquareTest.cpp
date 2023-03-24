#include "ModernChess/Square.h"

#include <gtest/gtest.h>

namespace
{
    using namespace ModernChess;

    TEST(BitBoardOperationsTest, occupyAndEraseSquare)
    {
        EXPECT_EQ(squareToCoordinates[Square::a1],  "a1");
        EXPECT_EQ(squareToCoordinates[Square::a8],  "a8");
        EXPECT_EQ(squareToCoordinates[Square::h1],  "h1");
        EXPECT_EQ(squareToCoordinates[Square::h8],  "h8");
    }
}