#include "ModernChess/FenParsing.h"
#include "ModernChess/Evaluation.h"

#include <gtest/gtest.h>

using namespace ModernChess;

namespace
{
    class ExtendedEvaluation : public Evaluation
    {
    public:
        explicit ExtendedEvaluation(GameState gameState) : Evaluation(gameState) {}

        using ModernChess::Evaluation::scoreMove;
        using ModernChess::Evaluation::generateSortedMoves;
        using ModernChess::Evaluation::mvvLva;
    };

    TEST(EvaluationTest, FindCheckInOne)
    {
        /*
         * 8 ♔ . . . . . . .
         * 7 . . ♙ ♗ ♘ . . .
         * 6 . . ♘ ♞ ♙ . . .
         * 5 . . . ♙ . . . .
         * 4 ♞ . ♖ ♟︎ . . ♟︎ .
         * 3 ♟︎ ♛ ♖ . ♟︎ . . .
         * 2 . ♝ ♕ . . ♟︎ . ♟︎
         * 1 . . . . ♚ . . ♜
         *
         *   a b c d e f g h
         */
        constexpr auto fenString = "k7/2pbn3/2nNp3/3p4/N1rP2P1/PQr1P3/1Bq2P1P/4K2R w K - 0 26";
        FenParsing::FenParser fenParser(fenString);
        const GameState gameState = fenParser.parse();

        const Move move = Evaluation(gameState).getBestMove(5).bestMove;

        EXPECT_EQ(move.getFrom(), Square::b3);
        EXPECT_EQ(move.getTo(), Square::b7);
        EXPECT_EQ(move.getMovedFigure(), Figure::WhiteQueen);

        std::cout << gameState;
    }

    TEST(EvaluationTest, mvvLvaWhiteQueenTakesBlackPawn)
    {
        EXPECT_EQ(ExtendedEvaluation::mvvLva[Figure::WhiteQueen][Figure::BlackPawn], 101);
    }

    TEST(EvaluationTest, mvvLvaWhitePawnTakesBlackQueen)
    {
        EXPECT_EQ(ExtendedEvaluation::mvvLva[Figure::WhitePawn][Figure::BlackQueen], 505);
    }

    TEST(EvaluationTest, mvvLvaBlackPawnTakesWhiteQueen)
    {
        EXPECT_EQ(ExtendedEvaluation::mvvLva[Figure::BlackPawn][Figure::WhiteQueen], 505);
    }

    TEST(EvaluationTest, mvvLvaBlackPawnTakesWhiteKing)
    {
        EXPECT_EQ(ExtendedEvaluation::mvvLva[Figure::BlackPawn][Figure::WhiteKing], 605);
    }

    TEST(EvaluationTest, mvvLvaWhitePawnTakesBlackKing)
    {
        EXPECT_EQ(ExtendedEvaluation::mvvLva[Figure::WhitePawn][Figure::BlackKing], 605);
    }

    TEST(EvaluationTest, scoreEnpassantMoveWithWhitePawnTakesBlackPawn)
    {
        /*
         * 8 . . . . ♔ . . .
         * 7 . . . . . . . .
         * 6 . . . . . . . .
         * 5 . . . . ♟︎ ♙ . .
         * 4 . . . . . . . .
         * 3 . . . . . . . .
         * 2 . . . . . . . .
         * 1 . . . . ♚ . . .
         *
         *   a b c d e f g h
         */
        constexpr auto enPassantPosition = "4k3/8/8/4Pp2/8/8/8/4K3 w - f6 0 1";
        FenParsing::FenParser fenParser(enPassantPosition);
        const GameState gameState = fenParser.parse();

        const Move move(Square::e5, Square::f6, Figure::WhitePawn, Figure::None, true, false, true, false);
        const ExtendedEvaluation evaluation(gameState);

        EXPECT_EQ(evaluation.scoreMove(move), 105);
    }

    TEST(EvaluationTest, SortMoves)
    {
        /*
         * 8 ♔ . . . . . . .
         * 7 . . ♙ ♗ ♘ . . .
         * 6 . . ♘ ♞ ♙ . . .
         * 5 . . . ♙ . . . .
         * 4 ♞ . ♖ ♟︎ . . ♟︎ .
         * 3 ♟︎ ♛ ♖ . ♟︎ . . .
         * 2 . ♝ ♕ . . ♟︎ . ♟︎
         * 1 . . . . ♚ . . ♜
         *
         *   a b c d e f g h
         */
        constexpr auto fenString = "k7/2pbn3/2nNp3/3p4/N1rP2P1/PQr1P3/1Bq2P1P/4K2R w K - 0 26";
        FenParsing::FenParser fenParser(fenString);
        const GameState gameState = fenParser.parse();

        ExtendedEvaluation evaluation(gameState);
        const std::vector<Move> moves = evaluation.generateSortedMoves();

        int32_t lastScore = std::numeric_limits<int32_t>::max();

        for (const Move move : moves)
        {
            const int32_t newScore = evaluation.scoreMove(move);
            std::cout << move << " scores "  << newScore << ", ";
            EXPECT_TRUE(lastScore >= newScore);
            lastScore = newScore;
        }
    }
}