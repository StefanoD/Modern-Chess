#include "ModernChess/UCIParser.h"

#include <gtest/gtest.h>

namespace {
    using namespace ModernChess;

    TEST(UCIParserTest, parseMove)
    {
        {
            UCIParser parser("e2e3");

            const UCIParser::UCIMove move = parser.parseMove();

            EXPECT_EQ(move.sourceSquare, Square::e2);
            EXPECT_EQ(move.targetSquare, Square::e3);
            EXPECT_FALSE(move.legalPromotionCharacter);
        }

        {
            UCIParser parser("e2e3 ");

            const UCIParser::UCIMove move = parser.parseMove();

            EXPECT_EQ(move.sourceSquare, Square::e2);
            EXPECT_EQ(move.targetSquare, Square::e3);
            EXPECT_FALSE(move.legalPromotionCharacter);
        }
    }

    TEST(UCIParserTest, parseMoveWithQueenPromition)
    {
        UCIParser parser("e2e3q");

        const UCIParser::UCIMove move = parser.parseMove();

        EXPECT_EQ(move.sourceSquare, Square::e2);
        EXPECT_EQ(move.targetSquare, Square::e3);
        EXPECT_TRUE(move.legalPromotionCharacter);
    }

    TEST(UCIParserTest, parseMoveWithQueenPromitionAndWhitespacePrefix)
    {
        UCIParser parser(" e2e3q");

        const UCIParser::UCIMove move = parser.parseMove();

        EXPECT_EQ(move.sourceSquare, Square::e2);
        EXPECT_EQ(move.targetSquare, Square::e3);
        EXPECT_TRUE(move.legalPromotionCharacter);
    }

    TEST(UCIParserTest, parseMoveIllegalPromotionCharacter)
    {
        UCIParser parser("e2e3f");

        const UCIParser::UCIMove move = parser.parseMove();

        EXPECT_EQ(move.sourceSquare, Square::undefined);
        EXPECT_EQ(move.targetSquare, Square::undefined);
        EXPECT_FALSE(move.legalPromotionCharacter);
    }

    TEST(UCIParserTest, sendTimeForWhite)
    {
        UCIParser parser("wtime");
        EXPECT_TRUE(parser.uiHasSentTimeForWhite());
    }

    TEST(UCIParserTest, sendTimeForBlack)
    {
        UCIParser parser("btime");
        EXPECT_TRUE(parser.uiHasSentTimeForBlack());
    }

    TEST(UCIParserTest, sendTimeIncrementForWhite)
    {
        UCIParser parser("winc");
        EXPECT_TRUE(parser.uiHasSentWhiteIncrement());
    }

    TEST(UCIParserTest, sendTimeIncrementForBlack)
    {
        UCIParser parser("binc");
        EXPECT_TRUE(parser.uiHasSentBlackIncrement());
    }

    TEST(UCIParserTest, sendMovesToGo)
    {
        UCIParser parser("movestogo");
        EXPECT_TRUE(parser.uiHasSentMovesToGo());
    }
}