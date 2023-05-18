#include "ModernChess/BasicParser.h"

#include <gtest/gtest.h>

using namespace ModernChess;

namespace
{
    TEST(BasicParserTest, Init)
    {
        BasicParser parser("1");

        EXPECT_FALSE(parser.hasNextCharacter());
    }

}