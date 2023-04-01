#include "ModernChess/SlidingPieceAttackGeneration.h"
#include "ModernChess/Utilities.h"

#include <gtest/gtest.h>

namespace {
    using namespace ModernChess;

    TEST(SlidingPieceAttackGeneration, maskBishopAttacksD4)
    {
        const BitBoardState board = AttackGeneration::SlidingPieces::maskBishopAttacks(d4);;


        const std::vector<Square> expectedOccupiedSquares{
                    b2,             f2,
                        c3,     e3,
                //          d4
                        c5,     e5,
                    b6,             f6,
                                        g7,
        };

        const std::vector<Square> expectedEmptySquares{
                a1, b1, c1, d1, e1, f1, g1, h1,
                a2,     c2, d2, e2,     g2, h2,
                a3, b3,     d3,     f3, g3, h3,
                a4, b4, c4, d4, e4, f4, g4, h4,
                a5, b5,     d5,     f5, g5, h5,
                a6,     c6, d6, e6,     g6, h6,
                a7, b7, c7, d7, e7, f7,     h7,
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