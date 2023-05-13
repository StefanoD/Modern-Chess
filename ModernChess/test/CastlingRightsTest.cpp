#include "ModernChess/CastlingRights.h"

#include <gtest/gtest.h>

namespace
{
    using namespace ModernChess;

    TEST(CastlingRightsTest, WhiteKingMove)
    {
        const CastlingRights castlingRightsBeforeMove = CastlingRights(CastlingRights::WhiteAnySide | CastlingRights::BlackAnySide);
        const Square from = Square::e1;
        const Square to = Square::f1;

        const CastlingRights castleRightsAfterMove = updateCastleRights(castlingRightsBeforeMove, from, to);

        // White can't castle anymore
        EXPECT_EQ(castleRightsAfterMove, CastlingRights::BlackAnySide);
    }
}


