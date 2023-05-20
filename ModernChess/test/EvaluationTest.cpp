#include "ModernChess/FenParsing.h"
#include "ModernChess/Evaluation.h"

#include <gtest/gtest.h>

using namespace ModernChess;

namespace
{
    TEST(EvaluationTest, SimpleTestPosition)
    {
        /*
         * 8 ♖ ♘ ♗ ♕ ♔ ♗ ♘ ♖
         * 7 ♙ ♙ ♙ ♙ . ♙ ♙ ♙
         * 6 . . . . . . . .
         * 5 . . . . ♙ . . .  // Black & White are position equalizing to 0
         * 4 . . . . ♟︎ . . .
         * 3 . . . . . ♞ . . // New knight position counts 20
         * 2 ♟︎ ♟︎ ♟︎ ♟︎ . ♟︎ ♟︎ ♟︎
         * 1 ♜ ♞ ♝ ♛ ♚ ♝ . ♜ // This empty square counts -10
         *
         *   a b c d e f g h
         */
        FenParsing::FenParser fenParser("rnbqkbnr/pppp1ppp/8/4p3/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq - 0 1");
        const GameState gameState = fenParser.parse();

        const int score = Evaluation::evaluatePosition(gameState.board.sideToMove, gameState.board.bitboards);

        std::cout << gameState;

        EXPECT_EQ(score, 30);
    }
}