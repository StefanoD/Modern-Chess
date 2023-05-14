#include "ModernChess/CastlingRights.h"

#include <gtest/gtest.h>

namespace
{
    using namespace ModernChess;

    TEST(CastlingRightsTest, WhiteKingMove)
    {
        const CastlingRights castlingRightsBeforeMove{CastlingRights::WhiteAnySide | CastlingRights::BlackAnySide};
        const Square from = Square::e1;
        const Square to = Square::f1;

        const CastlingRights castleRightsAfterMove = updateCastleRights(castlingRightsBeforeMove, from, to);

        // White can't castle anymore
        EXPECT_EQ(castleRightsAfterMove, CastlingRights::BlackAnySide);
    }

    TEST(CastlingRightsTest, WhiteRookKingSideMove)
    {
        const CastlingRights castlingRightsBeforeMove{CastlingRights::WhiteAnySide | CastlingRights::BlackAnySide};
        const Square from = Square::h1;
        const Square to = Square::h2;

        const CastlingRights castleRightsAfterMove = updateCastleRights(castlingRightsBeforeMove, from, to);

        EXPECT_EQ(castleRightsAfterMove, CastlingRights(CastlingRights::WhiteQueenSide | CastlingRights::BlackAnySide));
    }

    TEST(CastlingRightsTest, WhiteRookQueenSideMove)
    {
        const CastlingRights castlingRightsBeforeMove{CastlingRights::WhiteAnySide | CastlingRights::BlackAnySide};
        const Square from = Square::a1;
        const Square to = Square::a2;

        const CastlingRights castleRightsAfterMove = updateCastleRights(castlingRightsBeforeMove, from, to);

        EXPECT_EQ(castleRightsAfterMove, CastlingRights(CastlingRights::WhiteKingSide | CastlingRights::BlackAnySide));
    }

    TEST(CastlingRightsTest, BlackKingMove)
    {
        const CastlingRights castlingRightsBeforeMove{CastlingRights::WhiteAnySide | CastlingRights::BlackAnySide};
        const Square from = Square::e8;
        const Square to = Square::f8;

        const CastlingRights castleRightsAfterMove = updateCastleRights(castlingRightsBeforeMove, from, to);

        // Black can't castle anymore
        EXPECT_EQ(castleRightsAfterMove, CastlingRights::WhiteAnySide);
    }

    TEST(CastlingRightsTest, BlackRookKingSideMove)
    {
        const CastlingRights castlingRightsBeforeMove{CastlingRights::WhiteAnySide | CastlingRights::BlackAnySide};
        const Square from = Square::h8;
        const Square to = Square::h7;

        const CastlingRights castleRightsAfterMove = updateCastleRights(castlingRightsBeforeMove, from, to);

        EXPECT_EQ(castleRightsAfterMove, CastlingRights(CastlingRights::BlackQueenSide | CastlingRights::WhiteAnySide));
    }

    TEST(CastlingRightsTest, BlackRookQueenSideMove)
    {
        const CastlingRights castlingRightsBeforeMove{CastlingRights::WhiteAnySide | CastlingRights::BlackAnySide};
        const Square from = Square::a8;
        const Square to = Square::a7;

        const CastlingRights castleRightsAfterMove = updateCastleRights(castlingRightsBeforeMove, from, to);

        EXPECT_EQ(castleRightsAfterMove, CastlingRights(CastlingRights::BlackKingSide | CastlingRights::WhiteAnySide));
    }

    TEST(CastlingRightsTest, PawnMove)
    {
        const CastlingRights castlingRightsBeforeMove{CastlingRights::WhiteAnySide | CastlingRights::BlackAnySide};
        const Square from = Square::d2;
        const Square to = Square::d4;

        const CastlingRights castleRightsAfterMove = updateCastleRights(castlingRightsBeforeMove, from, to);

        // Black can't castle anymore
        EXPECT_EQ(castleRightsAfterMove, castlingRightsBeforeMove);
    }
}


