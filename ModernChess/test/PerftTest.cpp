#include "TestingPositions.h"
#include "ModernChess/PerftLib/PerformanceTest.h"

#include <gtest/gtest.h>

namespace
{
    using namespace ModernChess::Perft;

    // See Perf Results https://www.chessprogramming.org/Perft_Results

    TEST(PerftTest, TestPosition2Depth1To5)
    {
        PerformanceTest test(TestingPositions::Position2);

        EXPECT_EQ(test.executePerformanceTest(1), 48);
        EXPECT_EQ(test.executePerformanceTest(2), 2039);
        EXPECT_EQ(test.executePerformanceTest(3), 97862);
        EXPECT_EQ(test.executePerformanceTest(4), 4085603);
        EXPECT_EQ(test.executePerformanceTest(5), 193690690);
    }

    TEST(PerftTest, TestPosition3Depth1To7)
    {
        PerformanceTest test(TestingPositions::Position3);

        EXPECT_EQ(test.executePerformanceTest(1), 14);
        EXPECT_EQ(test.executePerformanceTest(2), 191);
        EXPECT_EQ(test.executePerformanceTest(3), 2812);
        EXPECT_EQ(test.executePerformanceTest(4), 43238);
        EXPECT_EQ(test.executePerformanceTest(5), 674624);
        EXPECT_EQ(test.executePerformanceTest(6), 11030083);
        EXPECT_EQ(test.executePerformanceTest(7), 178633661);
    }

    TEST(PerftTest, TestPosition4Depth1To6)
    {
        PerformanceTest test(TestingPositions::Position4);

        EXPECT_EQ(test.executePerformanceTest(1), 6);
        EXPECT_EQ(test.executePerformanceTest(2), 264);
        EXPECT_EQ(test.executePerformanceTest(3), 9467);
        EXPECT_EQ(test.executePerformanceTest(4), 422333);
        EXPECT_EQ(test.executePerformanceTest(5), 15833292);
        EXPECT_EQ(test.executePerformanceTest(6), 706045033);
    }

    TEST(PerftTest, TestPosition5Depth1To5)
    {
        PerformanceTest test(TestingPositions::Position5);

        EXPECT_EQ(test.executePerformanceTest(1), 44);
        EXPECT_EQ(test.executePerformanceTest(2), 1486);
        EXPECT_EQ(test.executePerformanceTest(3), 62379);
        EXPECT_EQ(test.executePerformanceTest(4), 2103487);
        EXPECT_EQ(test.executePerformanceTest(5), 89941194);
    }

    TEST(PerftTest, TestPosition6Depth1To5)
    {
        PerformanceTest test(TestingPositions::Position6);

        EXPECT_EQ(test.executePerformanceTest(1), 46);
        EXPECT_EQ(test.executePerformanceTest(2), 2079);
        EXPECT_EQ(test.executePerformanceTest(3), 89890);
        EXPECT_EQ(test.executePerformanceTest(4), 3894594);
        EXPECT_EQ(test.executePerformanceTest(5), 164075551);
    }
}