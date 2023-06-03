#include "BoardHelperUtility.h"
#include "ModernChess/Utilities.h"

#include <gtest/gtest.h>

namespace
{
    using namespace ModernChess;

    

    class ExtendedBoard : public Board
    {
    public:

        ExtendedBoard()
        {
            const Board board = Testing::initBoard();
            bitboards = board.bitboards;
            occupancies = board.occupancies;
            enPassantTarget = board.enPassantTarget;
            sideToMove = board.sideToMove;
            castlingRights = board.castlingRights;
        }

        BitBoardState getBitBoardConjunctions()
        {
            return bitboards[Figure::BlackRook] &
                   bitboards[Figure::BlackKnight] &
                   bitboards[Figure::BlackBishop] &
                   bitboards[Figure::BlackQueen] &
                   bitboards[Figure::BlackKing] &
                   bitboards[Figure::BlackPawn] &
                   bitboards[Figure::WhiteRook] &
                   bitboards[Figure::WhiteKnight] &
                   bitboards[Figure::WhiteBishop] &
                   bitboards[Figure::WhiteQueen] &
                   bitboards[Figure::WhiteKing] &
                   bitboards[Figure::WhitePawn];
        }
    };



    TEST(Board, SquaresAreUniquelyOccupied)
    {
        ExtendedBoard board;

        // This tests, that figures don't occupy the same square
        EXPECT_EQ(board.getBitBoardConjunctions(), 0U);

        const BitBoardState bitBoardState = board.occupancies[Color::Both];

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
        Board board = Testing::initBoard();
        board.bitboards = {};
        board.occupancies = {};

        board.bitboards[Figure::BlackPawn] = BitBoardOperations::occupySquare(BoardState::empty, Square::a8);

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
        const Board board = Testing::initBoard();
        const BitBoardState bitBoardState = board.occupancies[Color::Black];

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
        const Board board = Testing::initBoard();
        const BitBoardState bitBoardState = board.occupancies[Color::White];

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

    TEST(Board, GetEmptySquares)
    {
        const Board board = Testing::initBoard();
        const BitBoardState emptySquares = ~board.occupancies[Color::Both];

        // Empty and occupied squares must be disjoint.
        // This can be tested with logical AND-operator and testing to 0.
        // See https://www.chessprogramming.org/General_Setwise_Operations
        EXPECT_EQ(board.occupancies[Color::White] & emptySquares, 0);
        EXPECT_EQ(board.occupancies[Color::Black] & emptySquares, 0);
    }
}


