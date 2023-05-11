#include "ModernChess/Utilities.h"

#include <gtest/gtest.h>

using namespace ModernChess;

namespace {
    TEST(UtilitiesTest, TestMoveListPrint)
    {
        std::vector<Move> moveList{
                Move{Square::a1, Square::h1, Figure::WhiteRook, Figure::None, true, false, false, false},
        };

        for (int i = 0; i < 100; ++i)
        {
            moveList.emplace_back(Square::a2, Square::b4, Figure::WhitePawn, Figure::WhiteQueen, true, true, true,
                                  true);
        }

        std::cout << moveList;
    }
}