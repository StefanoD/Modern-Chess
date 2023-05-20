#include "ModernChess/BasicParser.h"

#include <gtest/gtest.h>

using namespace ModernChess;

namespace
{

    class ExtendedBasicParser : public BasicParser
    {
    public:
        explicit ExtendedBasicParser(std::string_view fen) : BasicParser(fen) {}
        using ModernChess::BasicParser::m_beginPos;
        using ModernChess::BasicParser::m_currentPos;
        using ModernChess::BasicParser::m_endPos;
    };

    TEST(BasicParserTest, Init)
    {
        const BasicParser parser("1");

        EXPECT_FALSE(parser.hasNextCharacter());
    }

    TEST(BasicParserTest, skipWhiteSpaces)
    {
        ExtendedBasicParser parser("      1");
        parser.skipWhiteSpaces();
        EXPECT_EQ('1', *parser.m_currentPos);
    }

    TEST(BasicParserTest, getNextString)
    {
        ExtendedBasicParser parser("      12   3");
        EXPECT_EQ("12", parser.getNextString());
        EXPECT_EQ("3", parser.getNextString());
    }

    TEST(BasicParserTest, parseNumber)
    {
        BasicParser parser("12");
        EXPECT_EQ(12, parser.parseNumber());
    }

    TEST(BasicParserTest, parseNumberWithWhitespaces)
    {
        BasicParser parser("      12   3");
        EXPECT_EQ(12, parser.parseNumber());
        EXPECT_EQ(3, parser.parseNumber());
    }
}