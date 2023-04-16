#include "ModernChess/AttackQueries.h"
#include "ModernChess/Utilities.h"
#include "ModernChess/FenParsing.h"

#include <gtest/gtest.h>

namespace {
    using namespace ModernChess;
    using namespace ModernChess::FenParsing;

    TEST(AttackQueriesTest, whitePawnOnD4BlackPawnOnC5)
    {
        const auto fenString = "7k/8/8/2p5/3P4/8/8/7K w - - 0 1";
        FenParser fenParser;
        const GameState gameState = fenParser.parse(fenString);
        // Occupy White pawnAttackTable on d4
        const bool ableToCaptureEast = AttackQueries::squareIsAttackedByWhite(gameState.board, Square::e5);

        EXPECT_TRUE(ableToCaptureEast);

        printAttackedSquares(std::cout, gameState.board, Color::White) << std::endl;

        std::cout << gameState;
    }
}