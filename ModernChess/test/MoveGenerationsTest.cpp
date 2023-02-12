#include "ModernChess/BitBoard.h"
#include "ModernChess/BitBoardOperations.h"
#include "ModernChess/MoveGenerations.h"
#include "ModernChess/Utilities.h"

#include <gtest/gtest.h>

namespace
{
    using namespace ModernChess;
    using namespace ModernChess::MoveGenerations;

    TEST(MoveGenerationsTest, OneStepNorth)
    {
        const BitBoard board; // Has initial board state with correct positions

        // All figures have been moved one step north
        const BitBoardState bitBoardState = MoveGenerations::oneStepNorth(board.getOccupiedSquares());

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

    TEST(MoveGenerationsTest, OneStepSouth)
    {
        const BitBoard board; // Has initial board state with correct positions

        // All figures have been moved one step north
        const BitBoardState bitBoardState = MoveGenerations::oneStepSouth(board.getOccupiedSquares());

        // Test if squares are occupied
        for (Square square = Square::a1; square <= Square::h1; ++square)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test for un-occupation of white figures
        for (Square square = Square::a2; square <= Square::h5; ++square)
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

    TEST(MoveGenerationsTest, OneStepEast)
    {
        const BitBoard board; // Has initial board state with correct positions

        // All figures have been moved one step north
        const BitBoardState bitBoardState = MoveGenerations::oneStepEast(board.getOccupiedSquares());

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

    TEST(MoveGenerationsTest, OneStepWest)
    {
        const BitBoard board; // Has initial board state with correct positions

        // All figures have been moved one step north
        const BitBoardState bitBoardState = MoveGenerations::oneStepWest(board.getOccupiedSquares());

        // Test if squares are occupied
        for (Square square = Square::b1; square <= Square::g1; ++square)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test for occupation of white figures
        for (Square square = Square::b2; square <= Square::g2; ++square)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test for occupation of black figures
        for (Square square = Square::a7; square <= Square::g7; ++square)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test for occupation of black figures
        for (Square square = Square::a8; square <= Square::g8; ++square)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        const BitBoardState aFile = bitBoardState & BitBoardConstants::hFile;
        // Because the pieces moved to west, we expect the complete h-file to be empty!
        EXPECT_EQ(aFile, BoardState::empty);

        print(std::cout, bitBoardState) << std::endl;
    }

    TEST(MoveGenerationsTest, OneStepSouthWest)
    {
        const BitBoard board; // Has initial board state with correct positions

        // All figures have been moved one step north
        const BitBoardState bitBoardState = MoveGenerations::oneStepSouthWest(board.getOccupiedSquares());

        // Test if squares are occupied
        for (Square square = Square::a1; square <= Square::g1; ++square)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test for un-occupation of white figures
        for (Square square = Square::a2; square <= Square::h5; ++square)
        {
            EXPECT_FALSE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test for occupation of black figures
        for (Square square = Square::a6; square <= Square::g6; ++square)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test for occupation of black figures
        for (Square square = Square::a7; square <= Square::g7; ++square)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test for un-occupation of black figures
        for (Square square = Square::a8; square <= Square::h8; ++square)
        {
            EXPECT_FALSE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        const BitBoardState aFile = bitBoardState & BitBoardConstants::hFile;
        // Because the pieces moved to east, we expect the complete h-file to be empty!
        EXPECT_EQ(aFile, BoardState::empty);

        print(std::cout, bitBoardState) << std::endl;
    }

    TEST(MoveGenerationsTest, KnightsNorthNorthEast)
    {
        // Occupy white pawn on d4
        BitBoardState knightsBoard = BitBoardOperations::occupySquare(BoardState::empty, Square::d4);
        knightsBoard = BitBoardOperations::occupySquare(knightsBoard, Square::c4);

        // Illegal moves
        knightsBoard = BitBoardOperations::occupySquare(knightsBoard, Square::a8);
        knightsBoard = BitBoardOperations::occupySquare(knightsBoard, Square::h8);

        // All figures have been moved one step north
        const BitBoardState board = MoveGenerations::Knights::northNorthEast(knightsBoard);

        const std::vector<Square> knightSquares {
               d6, e6,
        };

        const std::vector<Square> notOccupied {
                a1, b1, c1, d1, e1, f1, g1, h1,
                a2, b2, c2, d2, e2, f2, g2, h2,
                a3, b3, c3, d3, e3, f3, g3, h3,
                a4, b4, c4, d4, e4, f4, g4, h4,
                a5, b5, c5, d5, e5, f5, g5, h5,
                a6, b6, c6,         f6, g6, h6,
                a7, b7, c7, d7, e7, f7, g7, h7,
                a8, b8, c8, d8, e8, f8, g8, h8
        };

        for (const Square square : knightSquares)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(board, square));
        }

        for (const Square square : notOccupied)
        {
            EXPECT_FALSE(BitBoardOperations::isOccupied(board, square));
        }

        print(std::cout, board) << std::endl;
    }
}


