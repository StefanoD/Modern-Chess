#include "ModernChess/BitboardOperations.h"
#include "ModernChess/Utilities.h"

#include <gtest/gtest.h>

namespace
{
    using namespace ModernChess;

    TEST(BitBoardConstantsTest, AFile)
    {
        const BitBoardState board = BoardState::allSquaresOccupied & BitBoardConstants::aFile;

        const std::vector<Square> aFile {
                a1, a2, a3, a4, a5, a6, a7, a8,
        };

        const std::vector<Square> notAFile {
                b1, c1, d1, e1, f1, g1, h1,
                b2, c2, d2, e2, f2, g2, h2,
                b3, c3, d3, e3, f3, g3, h3,
                b4, c4, d4, e4, f4, g4, h4,
                b5, c5, d5, e5, f5, g5, h5,
                b6, c6, d6, e6, f6, g6, h6,
                b7, c7, d7, e7, f7, g7, h7,
                b8, c8, d8, e8, f8, g8, h8
        };

        for (Square square : aFile)
        {
            EXPECT_TRUE(BitboardOperations::isOccupied(board, square));
        }

        for (Square square : notAFile)
        {
            EXPECT_FALSE(BitboardOperations::isOccupied(board, square));
        }

        print(std::cout,board) << std::endl;
    }

    TEST(BitBoardConstantsTest, NotAFile)
    {
        const BitBoardState board = BoardState::allSquaresOccupied & BitBoardConstants::notAFile;

        const std::vector<Square> aFile {
                a1, a2, a3, a4, a5, a6, a7, a8,
        };

        const std::vector<Square> notAFile {
                b1, c1, d1, e1, f1, g1, h1,
                b2, c2, d2, e2, f2, g2, h2,
                b3, c3, d3, e3, f3, g3, h3,
                b4, c4, d4, e4, f4, g4, h4,
                b5, c5, d5, e5, f5, g5, h5,
                b6, c6, d6, e6, f6, g6, h6,
                b7, c7, d7, e7, f7, g7, h7,
                b8, c8, d8, e8, f8, g8, h8
        };

        for (Square square : aFile)
        {
            EXPECT_FALSE(BitboardOperations::isOccupied(board, square));
        }

        for (Square square : notAFile)
        {
            EXPECT_TRUE(BitboardOperations::isOccupied(board, square));
        }

        print(std::cout,board) << std::endl;
    }

    TEST(BitBoardConstantsTest, A1H8Diagonal)
    {
        const BitBoardState board = BoardState::allSquaresOccupied & BitBoardConstants::a1H8Diagonal;

        const std::vector<Square> a1H8Diagonal {
                a1, b2, c3, d4, e5, f6, g7, h8,
        };

        const std::vector<Square> notA1H8Diagonal {
                    b1, c1, d1, e1, f1, g1, h1,
                a2,     c2, d2, e2, f2, g2, h2,
                a3, b3,     d3, e3, f3, g3, h3,
                a4, b4, c4,     e4, f4, g4, h4,
                a5, b5, c5, d5,     f5, g5, h5,
                a6, b6, c6, d6, e6,     g6, h6,
                a7, b7, c7, d7, e7, f7,     h7,
                a8, b8, c8, d8, e8, f8, g8,
        };

        for (Square square : a1H8Diagonal)
        {
            EXPECT_TRUE(BitboardOperations::isOccupied(board, square));
        }

        for (Square square : notA1H8Diagonal)
        {
            EXPECT_FALSE(BitboardOperations::isOccupied(board, square));
        }

        print(std::cout,board) << std::endl;
    }

    TEST(BitBoardConstantsTest, HFile)
    {
        const BitBoardState board = BoardState::allSquaresOccupied & BitBoardConstants::hFile;

        const std::vector<Square> hFile {
                h1, h2, h3, h4, h5, h6, h7, h8
        };

        const std::vector<Square> notHFile {
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
            EXPECT_TRUE(BitboardOperations::isOccupied(board, square));
        }

        for (Square square : notHFile)
        {
            EXPECT_FALSE(BitboardOperations::isOccupied(board, square));
        }

        print(std::cout, board) << std::endl;
    }

    TEST(BitBoardConstantsTest, notHFile)
    {
        const BitBoardState board = BoardState::allSquaresOccupied & BitBoardConstants::notHFile;

        const std::vector<Square> hFile {
                h1, h2, h3, h4, h5, h6, h7, h8
        };

        const std::vector<Square> notHFile {
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

        print(std::cout, board) << std::endl;
    }

    TEST(BitBoardConstantsTest, FirstRank)
    {
        const BitBoardState board = BoardState::allSquaresOccupied & BitBoardConstants::firstRank;

        const std::vector<Square> firstRank {
                a1, b1, c1, d1, e1, f1, g1,
        };

        const std::vector<Square> notFirstRank {
                a2, b2, c2, d2, e2, f2, g2, h2,
                a3, b3, c3, d3, e3, f3, g3, h3,
                a4, b4, c4, d4, e4, f4, g4, h4,
                a5, b5, c5, d5, e5, f5, g5, h5,
                a6, b6, c6, d6, e6, f6, g6, h6,
                a7, b7, c7, d7, e7, f7, g7, h7,
                a8, b8, c8, d8, e8, f8, g8, h8
        };

        for (Square square : firstRank)
        {
            EXPECT_TRUE(BitboardOperations::isOccupied(board, square));
        }

        for (Square square : notFirstRank)
        {
            EXPECT_FALSE(BitboardOperations::isOccupied(board, square));
        }

        print(std::cout, board) << std::endl;
    }

    TEST(BitBoardConstantsTest, EightsRank)
    {
        const BitBoardState board = BoardState::allSquaresOccupied & BitBoardConstants::eightsRank;

        const std::vector<Square> eightsRank {
                a8, b8, c8, d8, e8, f8, g8, h8
        };

        const std::vector<Square> notEightsRank {
                a1, b1, c1, d1, e1, f1, g1, h1,
                a2, b2, c2, d2, e2, f2, g2, h2,
                a3, b3, c3, d3, e3, f3, g3, h3,
                a4, b4, c4, d4, e4, f4, g4, h4,
                a5, b5, c5, d5, e5, f5, g5, h5,
                a6, b6, c6, d6, e6, f6, g6, h6,
                a7, b7, c7, d7, e7, f7, g7, h7,
        };

        for (Square square : eightsRank)
        {
            EXPECT_TRUE(BitboardOperations::isOccupied(board, square));
        }

        for (Square square : notEightsRank)
        {
            EXPECT_FALSE(BitboardOperations::isOccupied(board, square));
        }

        print(std::cout, board) << std::endl;
    }
}


