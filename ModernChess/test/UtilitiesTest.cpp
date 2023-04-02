#include "ModernChess/Utilities.h"

#include <gtest/gtest.h>

namespace
{
    using namespace ModernChess;

    TEST(UtilitiesTest, getRandomNumber)
    {
        EXPECT_EQ(getRandomNumber(), 1741896308);
        EXPECT_EQ(getRandomNumber(), 321584506);
        EXPECT_EQ(getRandomNumber(), 3694591032);
        EXPECT_EQ(getRandomNumber(), 1972257248);
        EXPECT_EQ(getRandomNumber(), 200407065);
    }
}