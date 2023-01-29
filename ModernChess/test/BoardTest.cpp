#include "ModernChess/Board.h"

#include <gtest/gtest.h>

namespace
{
    class ExtendedBoard : public ModernChess::Board
    {
    public:

        ModernChess::BitBoard getBitBoardConjunctions()
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

    TEST(Board, SquaresAreUniquelyOccupied)
    {
        ExtendedBoard board;

        // This tests, that figures don't occupy the same square
        EXPECT_EQ(board.getBitBoardConjunctions().to_ulong(), 0U);

        const ModernChess::BitBoard bitBoardState = board.getOccupiedSquares();

        // Test occupation of white figures
        for (int square = 0; square < 16; ++square)
        {
            EXPECT_TRUE(bitBoardState[square]);
        }

        // Test occupation of white figures
        for (int square = 0; square < 16; ++square)
        {
            EXPECT_TRUE(bitBoardState[square]);
        }

        // Test if squares are not occupied
        for (int square = 16; square < 48; ++square)
        {
            EXPECT_FALSE(bitBoardState[square]);
        }

        // Test occupation of black figures
        for (int square = 48; square < 64; ++square)
        {
            EXPECT_TRUE(bitBoardState[square]);
        }

        std::cout << board.printOccupiedSquares() << std::endl;
    }

    TEST(Board, GetEmptySquares)
    {
        const ModernChess::Board board;
        const ModernChess::BitBoard occupiedSquares = board.getOccupiedSquares();
        const ModernChess::BitBoard emptySquares = board.getEmptySquares();

        // Empty and occupied squares must be disjoint. This can be tested with logical AND and testing to 0.
        // See https://www.chessprogramming.org/General_Setwise_Operations
        EXPECT_EQ(occupiedSquares & emptySquares, 0);
    }
}


