#include "ModernChess/FenParsing.h"
#include "ModernChess/Evaluation.h"

#include <gtest/gtest.h>

using namespace ModernChess;

namespace
{
    TEST(EvaluationTest, FindCheckInOne)
    {
        /*
         * 8 ♔ . . . . . . .
         * 7 . . ♙ ♗ ♘ . . .
         * 6 ♖ . ♘ ♞ ♙ . . .
         * 5 . . . ♙ . . . .
         * 4 ♞ . . ♟︎ . . ♟︎ .
         * 3 ♟︎ ♛ . . ♟︎ . . .
         * 2 . ♝ . . . ♟︎ . ♟︎
         * 1 . . . . ♚ . . ♜
         *
         *   a b c d e f g h
         */
        constexpr auto fenString = "k7/2pbn3/r1nNp3/3p4/N2P2P1/PQ2P3/1B3P1P/4K2R w K - 7 26";
        FenParsing::FenParser fenParser(fenString);
        const GameState gameState = fenParser.parse();

        const Move move = Evaluation(gameState).getBestMove(5).bestMove;

        EXPECT_EQ(move.getFrom(), Square::b3);
        EXPECT_EQ(move.getTo(), Square::b7);
        EXPECT_EQ(move.getMovedFigure(), Figure::WhiteQueen);
    }
}