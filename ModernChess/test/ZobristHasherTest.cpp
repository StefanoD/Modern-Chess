#include "ModernChess/FenParsing.h"
#include "TestingPositions.h"

#include <gtest/gtest.h>

using namespace ModernChess;

namespace
{
    TEST(ZobristHasherTest, TrickyPosition)
    {
        constexpr auto trickyPosition = TestingPositions::Position2;
        FenParsing::FenParser fenParser(trickyPosition);
        const GameState gameState = fenParser.parse();

        // Just checking for portability reasons if hashing is on all platforms the same
        EXPECT_EQ(gameState.gameStateHash, 0xed1ef6942fb0f13e);

        EXPECT_EQ(ZobristHasher::pieceKeys[11][63], uint64_t(17590421507200302306UL));
        EXPECT_EQ(ZobristHasher::castleKeys[0], uint64_t(14599039209436570616UL));
        EXPECT_EQ(ZobristHasher::castleKeys[15], uint64_t(12093051889040103024UL));
        EXPECT_EQ(ZobristHasher::sideKey, uint64_t(1772028295636336235UL));

        std::cout << gameState;
    }
}