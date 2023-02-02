#include "ModernChess/BitBoard.h"
#include "ModernChess/BitboardOperations.h"

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
        const std::string strBoard = BitBoard::printBitBoard(board);
        const size_t numberOfNewLines = 7;
        // Add also numberOfNewLines, because \n counts also as character
        const size_t position = 8 * numberOfNewLines + numberOfNewLines;
        EXPECT_EQ(strBoard.substr(position, 1), "1");
        std::cout << strBoard << std::endl;
    }

    TEST(Board, notHFile)
    {
        BitBoardState board = BoardState::allSquaresOccupied;
        board &= BitBoardConstants::notHFile;

        std::vector<Square> hFile {
            h1, h2, h3, h4, h5, h6, h7, h8
        };

        std::vector<Square> notHFile {
            a1, b1, c1, d1, e1, f1, g1,
            a2, b2, c2, d2, e2, f2, g2,
            a3, b3, c3, d3, e3, f3, g3,
            a4, b4, c4, d4, e4, f4, g4,
            a5, b5, c5, d5, e5, f5, g5,
            a6, b6, c6, d6, e6, f6, g6,
            a7, b7, c7, d7, e7, f7, g7,
            a8, b8, c8, d8, e8, f8, g8,
        };

        for (Square square : hFile)
        {
            EXPECT_FALSE(BitboardOperations::isOccupied(board, square));
        }

        for (Square square : notHFile)
        {
            EXPECT_TRUE(BitboardOperations::isOccupied(board, square));
        }

        std::cout << BitBoard::printBitBoard(board) << std::endl;
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

        std::cout << board.printBitBoard(bitBoardState) << std::endl;
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

        std::cout << board.printBitBoard(bitBoardState) << std::endl;
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

        std::cout << board.printBitBoard(bitBoardState) << std::endl;
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

        std::cout << board.printBitBoard(bitBoardState) << std::endl;
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


