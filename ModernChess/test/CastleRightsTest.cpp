#include "ModernChess/CastleRights.h"

#include <gtest/gtest.h>

namespace
{
    using namespace ModernChess;

    TEST(CastleRightsTest, WhiteKingMove)
    {
        const CastleRights castlingRightsBeforeMove = CastleRights(CastleRights::WhiteAnySide | CastleRights::BlackAnySide);
        const Square from = Square::e1;
        const Square to = Square::f1;

        const CastleRights castleRightsAfterMove = updateCastleRights(castlingRightsBeforeMove, from, to);

        // White can't castle anymore
        EXPECT_EQ(castleRightsAfterMove, CastleRights::BlackAnySide);
    }
}


