#include "ModernChess/BitBoard.h"
#include "ModernChess/BitBoardOperations.h"
#include "ModernChess/PawnPushes.h"
#include "ModernChess/Utilities.h"

#include <gtest/gtest.h>

namespace
{
    using namespace ModernChess;
    using namespace ModernChess::MoveGenerations;

    TEST(PawnPushesTest, OneStepNorth)
    {
        const BitBoard board; // Has initial board state with correct positions

        // All figures have been moved one step north
        const BitBoardState bitBoardState = MoveGenerations::oneStepNorth(board.getOccupiedSquares());

        // Test if squares are not occupied
        for (Square square = Square::a1; square <= Square::h1; ++square)
        {
            EXPECT_FALSE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test for occupation of White figures
        for (Square square = Square::a2; square <= Square::h3; ++square)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test for un-occupation of Black figures, because they moved north
        for (Square square = Square::a7; square <= Square::h7; ++square)
        {
            EXPECT_FALSE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test for occupation of Black figures
        for (Square square = Square::a8; square <= Square::h8; ++square)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        print(std::cout, bitBoardState) << std::endl;
    }

    TEST(PawnPushesTest, OneStepSouth)
    {
        const BitBoard board; // Has initial board state with correct positions

        // All figures have been moved one step north
        const BitBoardState bitBoardState = MoveGenerations::oneStepSouth(board.getOccupiedSquares());

        // Test if squares are occupied
        for (Square square = Square::a1; square <= Square::h1; ++square)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test for un-occupation of White figures
        for (Square square = Square::a2; square <= Square::h5; ++square)
        {
            EXPECT_FALSE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test for occupation of Black figures, because they moved south
        for (Square square = Square::a6; square <= Square::h7; ++square)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test for un-occupation of Black figures, because they moved south
        for (Square square = Square::a8; square <= Square::h8; ++square)
        {
            EXPECT_FALSE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        print(std::cout, bitBoardState) << std::endl;
    }

    TEST(PawnPushesTest, OneStepEast)
    {
        const BitBoard board; // Has initial board state with correct positions

        // All figures have been moved one step north
        const BitBoardState bitBoardState = MoveGenerations::oneStepEast(board.getOccupiedSquares());

        // Test if squares are occupied
        for (Square square = Square::b1; square <= Square::h1; ++square)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test for occupation of White figures
        for (Square square = Square::b2; square <= Square::h2; ++square)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test for occupation of Black figures
        for (Square square = Square::b7; square <= Square::h7; ++square)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test for occupation of Black figures
        for (Square square = Square::b8; square <= Square::h8; ++square)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        const BitBoardState aFile = bitBoardState & BitBoardConstants::aFile;
        // Because the pieces moved to east, we expect the complete a-file to be empty!
        EXPECT_EQ(aFile, BoardState::empty);

        print(std::cout, bitBoardState) << std::endl;
    }

    TEST(PawnPushesTest, OneStepWest)
    {
        const BitBoard board; // Has initial board state with correct positions

        // All figures have been moved one step north
        const BitBoardState bitBoardState = MoveGenerations::oneStepWest(board.getOccupiedSquares());

        // Test if squares are occupied
        for (Square square = Square::b1; square <= Square::g1; ++square)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test for occupation of White figures
        for (Square square = Square::b2; square <= Square::g2; ++square)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test for occupation of Black figures
        for (Square square = Square::a7; square <= Square::g7; ++square)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test for occupation of Black figures
        for (Square square = Square::a8; square <= Square::g8; ++square)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        const BitBoardState aFile = bitBoardState & BitBoardConstants::hFile;
        // Because the pieces moved to west, we expect the complete h-file to be empty!
        EXPECT_EQ(aFile, BoardState::empty);

        print(std::cout, bitBoardState) << std::endl;
    }

    TEST(PawnPushesTest, OneStepSouthWest)
    {
        const BitBoard board; // Has initial board state with correct positions

        // All figures have been moved one step north
        const BitBoardState bitBoardState = MoveGenerations::oneStepSouthWest(board.getOccupiedSquares());

        // Test if squares are occupied
        for (Square square = Square::a1; square <= Square::g1; ++square)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test for un-occupation of White figures
        for (Square square = Square::a2; square <= Square::h5; ++square)
        {
            EXPECT_FALSE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test for occupation of Black figures
        for (Square square = Square::a6; square <= Square::g6; ++square)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test for occupation of Black figures
        for (Square square = Square::a7; square <= Square::g7; ++square)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test for un-occupation of Black figures
        for (Square square = Square::a8; square <= Square::h8; ++square)
        {
            EXPECT_FALSE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        const BitBoardState aFile = bitBoardState & BitBoardConstants::hFile;
        // Because the pieces moved to east, we expect the complete h-file to be empty!
        EXPECT_EQ(aFile, BoardState::empty);

        print(std::cout, bitBoardState) << std::endl;
    }
}


