#include "ModernChess/BitBoard.h"
#include "ModernChess/BitboardOperations.h"
#include "ModernChess/Utilities.h"

#include <gtest/gtest.h>

namespace
{
    using namespace ModernChess;

    class ExtendedBoard : public BitBoard
    {
    public:

        BitBoardState getBitBoardConjunctions()
        {
            return m_blackRookBitBoard & \
                   m_blackKnightBitBoard & \
                   m_blackBishopBitBoard & \
                   m_blackQueenBitBoard & \
                   m_blackKingBitBoard & \
                   m_blackPawnBitBoard & \
                   m_whiteRookBitBoard & \
                   m_whiteKnightBitBoard & \
                   m_whiteBishopBitBoard & \
                   m_whiteQueenBitBoard & \
                   m_whiteKingBitBoard & \
                   m_whitePawnBitBoard;
        }
    };

    TEST(Board, BoardPrintBitBoard)
    {
        BitBoardState board = BoardState::empty;
        board = BitboardOperations::occupySquare(board, Square::a1);

        // We expect a1 to be on the left file on the 8. rank
        std::stringstream stream;
        print(stream, board);
        const std::string strBoard = stream.str();
        const size_t numberOfNewLines = 7;
        // Add also numberOfNewLines, because \n counts also as character
        const size_t position = 8 * numberOfNewLines + numberOfNewLines;
        EXPECT_EQ(strBoard.substr(position, 1), "1");
        std::cout << strBoard << std::endl;
    }

    TEST(Board, OneStepNorth)
    {
        BitBoard board; // Has initial board state with correct positions

        // All figures have been moved one step north
        const BitBoardState bitBoardState = BitboardOperations::oneStepNorth(board.getOccupiedSquares());

        // Test if squares are not occupied
        for (Square square = Square::a1; square <= Square::h1; ++square)
        {
            EXPECT_FALSE(BitboardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test for occupation of white figures
        for (Square square = Square::a2; square <= Square::h3; ++square)
        {
            EXPECT_TRUE(BitboardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test for un-occupation of black figures, because they moved north
        for (Square square = Square::a7; square <= Square::h7; ++square)
        {
            EXPECT_FALSE(BitboardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test for occupation of black figures
        for (Square square = Square::a8; square <= Square::h8; ++square)
        {
            EXPECT_TRUE(BitboardOperations::isOccupied(bitBoardState, Square(square)));
        }

        print(std::cout, bitBoardState) << std::endl;
    }

    TEST(Board, OneStepSouth)
    {
        BitBoard board; // Has initial board state with correct positions

        // All figures have been moved one step north
        const BitBoardState bitBoardState = BitboardOperations::oneStepSouth(board.getOccupiedSquares());

        // Test if squares are occupied
        for (Square square = Square::a1; square <= Square::h1; ++square)
        {
            EXPECT_TRUE(BitboardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test for un-occupation of white figures
        for (Square square = Square::a2; square <= Square::h3; ++square)
        {
            EXPECT_FALSE(BitboardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test for occupation of black figures, because they moved south
        for (Square square = Square::a6; square <= Square::h7; ++square)
        {
            EXPECT_TRUE(BitboardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test for un-occupation of black figures, because they moved south
        for (Square square = Square::a8; square <= Square::h8; ++square)
        {
            EXPECT_FALSE(BitboardOperations::isOccupied(bitBoardState, Square(square)));
        }

        print(std::cout, bitBoardState) << std::endl;
    }

    TEST(Board, OneStepEast)
    {
        BitBoard board; // Has initial board state with correct positions

        // All figures have been moved one step north
        const BitBoardState bitBoardState = BitboardOperations::oneStepEast(board.getOccupiedSquares());

        // Test if squares are occupied
        for (Square square = Square::b1; square <= Square::h1; ++square)
        {
            EXPECT_TRUE(BitboardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test for occupation of white figures
        for (Square square = Square::b2; square <= Square::h2; ++square)
        {
            EXPECT_TRUE(BitboardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test for occupation of black figures
        for (Square square = Square::b7; square <= Square::h7; ++square)
        {
            EXPECT_TRUE(BitboardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test for occupation of black figures
        for (Square square = Square::b8; square <= Square::h8; ++square)
        {
            EXPECT_TRUE(BitboardOperations::isOccupied(bitBoardState, Square(square)));
        }

        const BitBoardState aFile = bitBoardState & BitBoardConstants::aFile;
        // Because the pieces moved to east, we expect the complete a-file to be empty!
        EXPECT_EQ(aFile, BoardState::empty);

        print(std::cout, bitBoardState) << std::endl;
    }

    TEST(Board, SquaresAreUniquelyOccupied)
    {
        ExtendedBoard board;

        // This tests, that figures don't occupy the same square
        EXPECT_EQ(board.getBitBoardConjunctions(), 0U);

        const BitBoardState bitBoardState = board.getOccupiedSquares();

        // Test occupation of white figures
        for (Square square = Square::a1; square <= Square::h2; ++square)
        {
            EXPECT_TRUE(BitboardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test if squares are not occupied
        for (Square square = Square::a3; square <= Square::h6; ++square)
        {
            EXPECT_FALSE(BitboardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test occupation of black figures
        for (Square square = Square::a7; square <= Square::h8; ++square)
        {
            EXPECT_TRUE(BitboardOperations::isOccupied(bitBoardState, Square(square)));
        }

        print(std::cout, bitBoardState) << std::endl;
    }

    TEST(Board, BlackFiguresAreSet)
    {
        const BitBoard board;
        const BitBoardState bitBoardState = board.getBlackFigures();

        // Test if squares are not occupied
        for (Square square = Square::a1; square <= Square::h6; ++square)
        {
            EXPECT_FALSE(BitboardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test occupation of black figures
        for (Square square = Square::a7; square <= Square::h8; ++square)
        {
            EXPECT_TRUE(BitboardOperations::isOccupied(bitBoardState, Square(square)));
        }

        print(std::cout, bitBoardState) << std::endl;
    }

    TEST(Board, WhiteFiguresAreSet)
    {
        const BitBoard board;
        const BitBoardState bitBoardState = board.getWhiteFigures();

        // Test occupation of white figures
        for (Square square = Square::a1; square <= Square::h2; ++square)
        {
            EXPECT_TRUE(BitboardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test if squares are not occupied
        for (Square square = Square::a3; square <= Square::h8; ++square)
        {
            EXPECT_FALSE(BitboardOperations::isOccupied(bitBoardState, Square(square)));
        }

        print(std::cout, bitBoardState) << std::endl;
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


