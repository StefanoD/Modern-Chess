#include "ModernChess/RookAttacks.h"
#include "ModernChess/Utilities.h"

#include <gtest/gtest.h>

namespace {
    using namespace ModernChess;

    TEST(RookAttacksTest, maskRookAttacksD4)
    {
        const BitBoardState board = RookAttackHelperFunctions::maskRookAttacks(d4);

        const std::vector<Square> expectedOccupiedSquares{
                d2,
                d3,
                b4, c4, e4, f4, g4,
                d5,
                d6,
                d7,
        };

        const std::vector<Square> expectedEmptySquares{
                a1, b1, c1, d1, e1, f1, g1, h1,
                a2, b2, c2, e2, f2, g2, h2,
                a3, b3, c3, e3, f3, g3, h3,
                a2, d4, h4,
                a5, b5, c5, e5, f5, g5, h5,
                a6, b6, c6, e6, f6, g6, h6,
                a7, b7, c7, e7, f7, g7, h7,
                a8, b8, c8, d8, e8, f8, g8, h8,
        };

        for (const Square square: expectedOccupiedSquares)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(board, square));
        }

        for (const Square square: expectedEmptySquares)
        {
            EXPECT_FALSE(BitBoardOperations::isOccupied(board, square));
        }

        print(std::cout, board) << std::endl;
    }

    TEST(RookAttacks, getAttacksD4)
    {
        const BitBoardState playBoard = BitBoardOperations::occupySquare(BoardState::empty, Square::d6);
        const RookAttacks rookAttacks;
        const BitBoardState board = rookAttacks.getAttacks(Square::d4, playBoard);

        const std::vector<Square> expectedOccupiedSquares{
                a4, b4, c4, d1, d2, d3, d5, d6, e4, f4, g4, h4,
        };

        const std::vector<Square> expectedEmptySquares{
                a1, b1, c1, e1, f1, g1, h1,
                a2, b2, c2, e2, f2, g2, h2,
                a3, b3, c3, e3, f3, g3, h3,
                d4,
                a5, b5, c5, e5, f5, g5, h5,
                a6, b6, c6, e6, f6, g6, h6,
                a7, b7, c7, d7, e7, f7, g7, h7,
                a8, b8, c8, d8, e8, f8, g8, h8,
        };

        for (const Square square: expectedOccupiedSquares)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(board, square));
        }

        for (const Square square: expectedEmptySquares)
        {
            EXPECT_FALSE(BitBoardOperations::isOccupied(board, square));
        }

        print(std::cout, board) << std::endl;
    }

    TEST(RookAttacksTest, rookAttacksOnTheFlyD4)
    {
        const BitBoardState playBoard = BitBoardOperations::occupySquare(BoardState::empty, Square::d6);
        const BitBoardState board = RookAttackHelperFunctions::rookAttacksOnTheFly(playBoard, d4);

        const std::vector<Square> expectedOccupiedSquares{
                a4, b4, c4, d1, d2, d3, d5, d6, e4, f4, g4, h4,
        };

        const std::vector<Square> expectedEmptySquares{
                a1, b1, c1, e1, f1, g1, h1,
                a2, b2, c2, e2, f2, g2, h2,
                a3, b3, c3, e3, f3, g3, h3,
                d4,
                a5, b5, c5, e5, f5, g5, h5,
                a6, b6, c6, e6, f6, g6, h6,
                a7, b7, c7, d7, e7, f7, g7, h7,
                a8, b8, c8, d8, e8, f8, g8, h8,
        };

        for (const Square square: expectedOccupiedSquares)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(board, square));
        }

        for (const Square square: expectedEmptySquares)
        {
            EXPECT_FALSE(BitBoardOperations::isOccupied(board, square));
        }

        print(std::cout, board) << std::endl;
    }
}