#include "ModernChess/FenParsing.h"
#include "ModernChess/Evaluation.h"

#include <gtest/gtest.h>

using namespace ModernChess;

namespace
{
    TEST(EvaluationTest, SimpleTestPosition)
    {
        /*
         * 8 ♖ ♘ ♗ ♕ ♔ ♗ . ♖
         * 7 ♙ ♙ ♙ ♙ . ♙ ♙ ♙
         * 6 . . . . . ♘ . .
         * 5 . . . . ♙ . . .  // Black & White are position equalizing to 0
         * 4 . . . . ♟︎ . . .
         * 3 . . . . . ♞ . . // New knight position counts 20
         * 2 ♟︎ ♟︎ ♟︎ ♟︎ . ♟︎ ♟︎ ♟︎
         * 1 ♜ ♞ ♝ ♛ ♚ ♝ . ♜ // This empty square counts -10
         *
         *   a b c d e f g h
         */
        FenParsing::FenParser fenParser("rnbqkb1r/pppp1ppp/5n2/4p3/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq - 0 1");
        GameState gameState = fenParser.parse();

        const Move move = Evaluation(gameState).getBestMove(5);

        std::cout << "best move: " << move << std::endl;
        std::cout << gameState;
    }
}