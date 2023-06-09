#include "TestingPositions.h"
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

    TEST(EvaluationTest, FindMateInOne)
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

        const EvaluationResult evaluationResult = Evaluation(gameState).getBestMove(5);
        const Move move = evaluationResult.bestMove();

        EXPECT_EQ(move.getFrom(), Square::b3);
        EXPECT_EQ(move.getTo(), Square::b7);
        EXPECT_EQ(move.getMovedFigure(), Figure::WhiteQueen);

        std::cout << gameState << std::endl;
        std::cout << evaluationResult;
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
        ExtendedEvaluation evaluation(gameState);

        EXPECT_EQ(evaluation.scoreMove(move), 100105);
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
        //evaluation.m_historyMoves[Color::White][Figure::WhiteQueen][Square::b8] = 1000;
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

    TEST(EvaluationTest, PreventPotentialMateIn5ForWhite)
    {
        /*
         * 8 ♖ . . . ♖ . ♔ .
         * 7 . . ♙ . ♕ ♙ ♟︎ ♙
         * 6 ♙ . ♘ . . ♘ . ♛
         * 5 . . . . ♙ . ♞ .
         * 4 . . . ♙ ♟︎ . ♗ .
         * 3 ♙ ♟︎ . ♟︎ . . . .
         * 2 ♟︎ . ♟︎ . . ♟︎ ♟︎ .
         * 1 . . ♚ ♜ . ♝ . ♜
         *
         *   a b c d e f g h
         */
        constexpr auto fenString = "r3r1k1/2p1qpPp/p3bn1Q/4p1N1/1n1pP3/pP1P4/P1P2PP1/2KR1B1R b - - 4 17";
        FenParsing::FenParser fenParser(fenString);
        const GameState gameState = fenParser.parse();

        Evaluation evaluation(gameState);
        const EvaluationResult evalResult = evaluation.getBestMove(8);

        EXPECT_EQ(evalResult.bestMove().getFrom(), Square::e7);
        EXPECT_EQ(evalResult.bestMove().getTo(), Square::c5);
        EXPECT_EQ(evalResult.bestMove().getMovedFigure(), Figure::BlackQueen);
        EXPECT_FALSE(evalResult.bestMove().isCapture());

        std::cout << evalResult << std::endl;
    }


    TEST(EvaluationTest, MateIn5ForWhite)
    {
        /*
         * 8 ♖ . . . ♖ . ♔ .
         * 7 . . ♙ . ♕ ♙ ♟︎ ♙
         * 6 ♙ . ♘ . . ♘ . ♛
         * 5 . . . . ♙ . ♞ .
         * 4 . . . ♙ ♟︎ . ♗ .
         * 3 ♙ ♟︎ . ♟︎ . . . .
         * 2 ♟︎ . ♟︎ . . ♟︎ ♟︎ .
         * 1 . . ♚ ♜ . ♝ . ♜
         *
         *   a b c d e f g h
         */
        constexpr auto fenString = "r3r1k1/2p1qpPp/p4n1Q/4p1N1/1n1pP1b1/pP1P4/P1P2PP1/2KR1B1R w - - 5 18";
        FenParsing::FenParser fenParser(fenString);
        const GameState gameState = fenParser.parse();

        Evaluation evaluation(gameState);
        const EvaluationResult evalResult = evaluation.getBestMove(6);

        EXPECT_EQ(evalResult.bestMove().getFrom(), Square::g5);
        EXPECT_EQ(evalResult.bestMove().getTo(), Square::h7);
        EXPECT_EQ(evalResult.bestMove().getMovedFigure(), Figure::WhiteKnight);
        EXPECT_TRUE(evalResult.bestMove().isCapture());

        std::cout << evalResult << std::endl;
    }

    TEST(EvaluationTest, HistorySearchExample)
    {
        /*
         * 8 . . . . . . ♔ .
         * 7 . . . ♕ . ♙ ♙ .
         * 6 ♙ ♙ . . . . . ♙
         * 5 . ♖ . . . . . ♘
         * 4 . . . . . . . .
         * 3 . ♟︎ . . . ♟︎ ♟︎ .
         * 2 ♟︎ ♛ . . . . ♝ ♟︎
         * 1 . . ♜ . . . ♚ .
         *
         *   a b c d e f g h
         */
        constexpr auto fenString = "6k1/3q1pp1/pp5p/1r5n/8/1P3PP1/PQ4BP/2R3K1 w - - 0 1";
        FenParsing::FenParser fenParser(fenString);
        const GameState gameState = fenParser.parse();

        Evaluation evaluation(gameState);
        const EvaluationResult evalResult = evaluation.getBestMove(6);

        std::cout << gameState << std::endl;

        std::cout << evalResult << std::endl;
    }

    TEST(EvaluationTest, Zugzwang1)
    {
        /*
         * 8 . . . . . . . .
         * 7 . . . . . . . .
         * 6 ♙ . ♙ . . . . .
         * 5 . ♙ . . . . . ♙
         * 4 . ♟︎ . . . . . ♙
         * 3 . . . . . . . .
         * 2 ♟︎ ♟︎ ♟︎ . . ♚ . ♙
         * 1 . . . . ♜ . ♖ ♔
         *
         *   a b c d e f g h
         */
        FenParsing::FenParser fenParser(TestingPositions::Zugzwang1);
        const GameState gameState = fenParser.parse();

        std::cout << gameState << std::endl;

        Evaluation evaluation(gameState);
        const EvaluationResult evalResult = evaluation.getBestMove(6);

        EXPECT_EQ(evalResult.bestMove().getFrom(), Square::e1);
        EXPECT_EQ(evalResult.bestMove().getTo(), Square::f1);
        EXPECT_EQ(evalResult.bestMove().getMovedFigure(), Figure::WhiteRook);
        EXPECT_FALSE(evalResult.bestMove().isCapture());

        std::cout << evalResult << std::endl;
    }

    TEST(EvaluationTest, Zugzwang2)
    {
        /*
         * 8 . ♕ . ♔ . . . .
         * 7 . . ♜ ♖ . . . .
         * 6 . . . . . . . .
         * 5 . . ♛ . . . ♚ .
         * 4 . . . . . . . .
         * 3 . . . . . . . .
         * 2 . . . . . . . .
         * 1 . . . . . . . .
         *
         *   a b c d e f g h
         */
        FenParsing::FenParser fenParser(TestingPositions::Zugzwang2);
        const GameState gameState = fenParser.parse();

        std::cout << gameState << std::endl;

        Evaluation evaluation(gameState);
        const EvaluationResult evalResult = evaluation.getBestMove(4);

        EXPECT_EQ(evalResult.bestMove().getFrom(), Square::g5);
        EXPECT_EQ(evalResult.bestMove().getTo(), Square::h6);
        EXPECT_EQ(evalResult.bestMove().getMovedFigure(), Figure::WhiteKing);
        EXPECT_FALSE(evalResult.bestMove().isCapture());

        std::cout << evalResult << std::endl;
    }

    TEST(EvaluationTest, Zugzwang3)
    {
        /*
         * 8 . . . . . . . ♔
         * 7 . . . . . ♚ . .
         * 6 . . . . . ♟︎ . ♙
         * 5 . . . ♙ . . . .
         * 4 . . . . . . ♟︎ .
         * 3 . . . ♙ . . . .
         * 2 . . . . . . . .
         * 1 . . . . . . . .
         *
         *   a b c d e f g h
         */
        FenParsing::FenParser fenParser(TestingPositions::Zugzwang3);
        const GameState gameState = fenParser.parse();

        std::cout << gameState << std::endl;

        Evaluation evaluation(gameState);
        // depth 8 - 10 fails with f7e6. Depth 11 evaluates the best move again with f7e7
        const EvaluationResult evalResult = evaluation.getBestMove(7);

        EXPECT_EQ(evalResult.bestMove().getFrom(), Square::f7);
        EXPECT_EQ(evalResult.bestMove().getTo(), Square::e7);
        EXPECT_EQ(evalResult.bestMove().getMovedFigure(), Figure::WhiteKing);
        EXPECT_FALSE(evalResult.bestMove().isCapture());

        std::cout << evalResult << std::endl;
    }

    TEST(EvaluationTest, Zugzwang4)
    {
        /*
         * 8 . . . . . . . .
         * 7 . . . . . . ♝ .
         * 6 ♙ . . . . . ♙ .
         * 5 ♟︎ ♙ . . . . ♔ ♙
         * 4 . ♟︎ . . . . . ♖
         * 3 . . . . . ♟︎ . ♛
         * 2 . . . . ♕ . ♟︎ ♚
         * 1 . . . . . . . .
         *
         *   a b c d e f g h
         */
        FenParsing::FenParser fenParser(TestingPositions::Zugzwang4);
        const GameState gameState = fenParser.parse();

        std::cout << gameState << std::endl;

        Evaluation evaluation(gameState);
        const EvaluationResult evalResult = evaluation.getBestMove(7);

        EXPECT_EQ(evalResult.bestMove().getFrom(), Square::h3);
        EXPECT_EQ(evalResult.bestMove().getTo(), Square::h4);
        EXPECT_EQ(evalResult.bestMove().getMovedFigure(), Figure::WhiteQueen);
        EXPECT_TRUE(evalResult.bestMove().isCapture());

        std::cout << evalResult << std::endl;
    }

    TEST(EvaluationTest, Zugzwang5)
    {
        /*
         * 8 . . . . . . . .
         * 7 . . . . . . . .
         * 6 . ♙ . ♖ . ♔ . .
         * 5 ♙ . ♙ ♟︎ ♞ . ♙ .
         * 4 ♟︎ . . . ♚ ♘ ♟︎ .
         * 3 . ♟︎ . . . . . .
         * 2 . . . . . . . .
         * 1 . . . ♜ . . . .
         *
         *   a b c d e f g h
         */
        FenParsing::FenParser fenParser(TestingPositions::Zugzwang5);
        const GameState gameState = fenParser.parse();

        std::cout << gameState << std::endl;

        Evaluation evaluation(gameState);
        const EvaluationResult evalResult = evaluation.getBestMove(13);

        EXPECT_EQ(evalResult.bestMove().getFrom(), Square::f4);
        EXPECT_EQ(evalResult.bestMove().getTo(), Square::d5);
        EXPECT_EQ(evalResult.bestMove().getMovedFigure(), Figure::BlackKnight);
        EXPECT_TRUE(evalResult.bestMove().isCapture());

        std::cout << evalResult << std::endl;
    }
}