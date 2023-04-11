#include "ModernChess/QueenAttacks.h"
#include "ModernChess/Utilities.h"

#include <gtest/gtest.h>

namespace {
    using namespace ModernChess;

    static const BishopAttacks bishopAttacks;
    static const RookAttacks rookAttacks;

    TEST(QueenAttacksTest, queenAttackOnD4OnEmptyBoard)
    {
        const QueenAttacks queenAttacks(bishopAttacks, rookAttacks);

        const BitBoardState board = queenAttacks.getAttacks(d4, BoardState::empty);

        const std::vector<Square> expectedEmptySquares{
                    b1, c1,     e1, f1,     h1,
                a2,     c2,     e2,     g2, h2,
                a3, b3,             f3, g3, h3,
                            d4,
                a5, b5,             f5, g5, h5,
                a6,     c6,     e6,     g6, h6,
                    b7, c7,     e7, f7,     h7,
                a8, b8, c8,     e8, f8, g8,
        };

        const std::vector<Square> expectedOccupiedSquares{
                a1,         d1,         g1,
                    b2,     d2,     f2,
                        c3, d3, e3,
                a4, b4, c4,     e4, f4, g4, h4,
                        c5, d5, e5,
                    b6,     d6,     f6,
                a7,         d7,         g7,
                            d8,             h8
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

    TEST(QueenAttacksTest, queenAttackOnD4b2IsOccupied)
    {
        const QueenAttacks queenAttacks(bishopAttacks, rookAttacks);
        const BitBoardState playBoard = BitBoardOperations::occupySquare(BoardState::empty, Square::b2);
        const BitBoardState board = queenAttacks.getAttacks(d4, playBoard);

        const std::vector<Square> expectedEmptySquares{
                a1, b1, c1,     e1, f1,     h1,
                a2,     c2,     e2,     g2, h2,
                a3, b3,             f3, g3, h3,
                d4,
                a5, b5,             f5, g5, h5,
                a6,     c6,     e6,     g6, h6,
                b7, c7,     e7, f7,     h7,
                a8, b8, c8,     e8, f8, g8,
        };

        const std::vector<Square> expectedOccupiedSquares{
                        d1,         g1,
                        d2,     f2,
                c3, d3, e3,
                a4, b4, c4,     e4, f4, g4, h4,
                c5, d5, e5,
                b6,     d6,     f6,
                a7,         d7,         g7,
                d8,             h8
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