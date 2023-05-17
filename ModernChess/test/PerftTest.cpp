#include "TestingPositions.h"
#include "ModernChess/PerftLib/PerformanceTest.h"

#include <gtest/gtest.h>

namespace
{
    using namespace ModernChess::Perft;

    // See Perf Results https://www.chessprogramming.org/Perft_Results

    TEST(PerftTest, TestPosition2Depth5)
    {
        PerformanceTest test(TestingPositions::Position2);
        const uint64_t numberNodes = test.executePerformanceTest(5);

        EXPECT_EQ(numberNodes, 193690690);
    }
}