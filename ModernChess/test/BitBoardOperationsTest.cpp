#include "ModernChess/BitBoard.h"
#include "ModernChess/BitboardOperations.h"
#include "ModernChess/Utilities.h"

#include <gtest/gtest.h>

namespace
{
    using namespace ModernChess;

    TEST(BitBoardOperationsTest, OneStepNorth)
    {
        BitBoard board; // Has initial board state with correct positions

        // All figures have been moved one step north
        const BitBoardState bitBoardState = BitBoardOperations::oneStepNorth(board.getOccupiedSquares());

        // Test if squares are not occupied
        for (Square square = Square::a1; square <= Square::h1; ++square)
        {
            EXPECT_FALSE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test for occupation of white figures
        for (Square square = Square::a2; square <= Square::h3; ++square)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test for un-occupation of black figures, because they moved north
        for (Square square = Square::a7; square <= Square::h7; ++square)
        {
            EXPECT_FALSE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test for occupation of black figures
        for (Square square = Square::a8; square <= Square::h8; ++square)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        print(std::cout, bitBoardState) << std::endl;
    }

    TEST(BitBoardOperationsTest, OneStepSouth)
    {
        BitBoard board; // Has initial board state with correct positions

        // All figures have been moved one step north
        const BitBoardState bitBoardState = BitBoardOperations::oneStepSouth(board.getOccupiedSquares());

        // Test if squares are occupied
        for (Square square = Square::a1; square <= Square::h1; ++square)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test for un-occupation of white figures
        for (Square square = Square::a2; square <= Square::h3; ++square)
        {
            EXPECT_FALSE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test for occupation of black figures, because they moved south
        for (Square square = Square::a6; square <= Square::h7; ++square)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test for un-occupation of black figures, because they moved south
        for (Square square = Square::a8; square <= Square::h8; ++square)
        {
            EXPECT_FALSE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        print(std::cout, bitBoardState) << std::endl;
    }

    TEST(BitBoardOperationsTest, OneStepEast)
    {
        BitBoard board; // Has initial board state with correct positions

        // All figures have been moved one step north
        const BitBoardState bitBoardState = BitBoardOperations::oneStepEast(board.getOccupiedSquares());

        // Test if squares are occupied
        for (Square square = Square::b1; square <= Square::h1; ++square)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test for occupation of white figures
        for (Square square = Square::b2; square <= Square::h2; ++square)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test for occupation of black figures
        for (Square square = Square::b7; square <= Square::h7; ++square)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test for occupation of black figures
        for (Square square = Square::b8; square <= Square::h8; ++square)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        const BitBoardState aFile = bitBoardState & BitBoardConstants::aFile;
        // Because the pieces moved to east, we expect the complete a-file to be empty!
        EXPECT_EQ(aFile, BoardState::empty);

        print(std::cout, bitBoardState) << std::endl;
    }
}


