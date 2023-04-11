#include "ModernChess/BitBoard.h"
#include "ModernChess/BitBoardOperations.h"
#include "ModernChess/Utilities.h"
#include "ModernChess/Figure.h"

#include <gtest/gtest.h>

namespace
{
    using namespace ModernChess;

    class ExtendedBoard : public BitBoard
    {
    public:

        BitBoardState getBitBoardConjunctions()
        {
            return bitboards[FigureType::BlackRook] &
                   bitboards[FigureType::BlackKnight] &
                   bitboards[FigureType::BlackBishop] &
                   bitboards[FigureType::BlackQueen] &
                   bitboards[FigureType::BlackKing] &
                   bitboards[FigureType::BlackPawn] &
                   bitboards[FigureType::WhiteRook] &
                   bitboards[FigureType::WhiteKnight] &
                   bitboards[FigureType::WhiteBishop] &
                   bitboards[FigureType::WhiteQueen] &
                   bitboards[FigureType::WhiteKing] &
                   bitboards[FigureType::WhitePawn];
        }
    };


    TEST(Board, SquaresAreUniquelyOccupied)
    {
        ExtendedBoard board;

        // This tests, that figures don't occupy the same square
        EXPECT_EQ(board.getBitBoardConjunctions(), 0U);

        const BitBoardState bitBoardState = board.getOccupiedSquares();

        // Test occupation of White figures
        for (Square square = Square::a1; square <= Square::h2; ++square)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test if squares are not occupied
        for (Square square = Square::a3; square <= Square::h6; ++square)
        {
            EXPECT_FALSE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test occupation of Black figures
        for (Square square = Square::a7; square <= Square::h8; ++square)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        print(std::cout, bitBoardState) << std::endl;

        std::cout << board;
    }

    TEST(Board, BlackPawnAtA8)
    {
        BitBoard board;
        board.bitboards = {};
        board.occupancies = {};

        board.bitboards[FigureType::BlackPawn] = BitBoardOperations::occupySquare(BoardState::empty, Square::a8);

        std::stringstream streamPrintedBoard;
        streamPrintedBoard << board;

        const std::string printedBoard = streamPrintedBoard.str();

        // Make sure the black pawn is printed on the correct position,
        // and it is really a black pawn and not a white pawn
        EXPECT_TRUE(printedBoard.find("8 ♙ . . . . . . .") != std::string::npos);

        std::cout << board;
    }

    TEST(Board, BlackFiguresAreSet)
    {
        const BitBoard board;
        const BitBoardState bitBoardState = board.getBlackFigures();

        // Test if squares are not occupied
        for (Square square = Square::a1; square <= Square::h6; ++square)
        {
            EXPECT_FALSE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test occupation of Black figures
        for (Square square = Square::a7; square <= Square::h8; ++square)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        print(std::cout, bitBoardState) << std::endl;
    }

    TEST(Board, WhiteFiguresAreSet)
    {
        const BitBoard board;
        const BitBoardState bitBoardState = board.getWhiteFigures();

        // Test occupation of White figures
        for (Square square = Square::a1; square <= Square::h2; ++square)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test if squares are not occupied
        for (Square square = Square::a3; square <= Square::h8; ++square)
        {
            EXPECT_FALSE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
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


