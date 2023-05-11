#include "ModernChess/FenParsing.h"
#include "ModernChess/MoveGeneration.h"
#include "ModernChess/Utilities.h"

#include <gtest/gtest.h>

#include <algorithm>

using namespace ModernChess;
using namespace ModernChess::MoveGenerations;

namespace
{
    TEST(MoveGenerationTest, EnPassantCaptureWithBlackTest)
    {
        /*
         * 8 . . . . ♔ . . .
         * 7 . . . . . . . .
         * 6 . . . . . . . .
         * 5 . . . . . . . .
         * 4 . . . . ♟︎ ♙ . .
         * 3 . . . . . . . .
         * 2 . . . . . . . .
         * 1 . . . . ♚ . . .
         *
         *   a b c d e f g h
         */
        constexpr auto enPassantPosition = "4k3/8/8/8/4Pp2/8/8/4K3 b - e3 0 1";
        FenParsing::FenParser fenParser;
        const GameState gameState = fenParser.parse(enPassantPosition);

        std::vector<Move> generatedMoves;
        generatedMoves.reserve(16);

        MoveGeneration::generateBlackFigureMoves(gameState, generatedMoves);

        // En passant capture
        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::f4 &&
                   move.getTo() == Square::e3 &&
                   move.isCapture() &&
                   move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::BlackPawn &&
                   not move.isDoublePawnPush() &&
                   not move.isCastlingMove() &&
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::None;
        }));

        // Non-en passant capture
        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::f4 &&
                   move.getTo() == Square::f3 &&
                   not move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::BlackPawn &&
                   not move.isDoublePawnPush() &&
                   not move.isCastlingMove() &&
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::None;
        }));

        std::cout << generatedMoves << std::endl;
    }

    TEST(MoveGenerationTest, BlackKnightCapturesTest)
    {
        /*
         * 8 . . . . ♔ . . .
         * 7 . . . . . . . .
         * 6 . . . . . . . .
         * 5 . . ♟︎ . ♟︎ . . .
         * 4 . ♟︎ . . . ♟︎ . .
         * 3 . . . ♘ . . . .
         * 2 . ♟︎ . . . ♟︎ . .
         * 1 . . ♜ . ♚ . . .
         *
         *   a b c d e f g h
         */
        constexpr auto enPassantPosition = "4k3/8/8/2P1P3/1P3P2/3n4/1P3P2/2R1K3 b - - 0 1";
        FenParsing::FenParser fenParser;
        const GameState gameState = fenParser.parse(enPassantPosition);

        std::vector<Move> generatedMoves;
        generatedMoves.reserve(16);

        MoveGeneration::generateBlackFigureMoves(gameState, generatedMoves);

        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::d3 &&
                   move.getTo() == Square::c1 &&
                   move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::BlackKnight &&
                   not move.isDoublePawnPush() &&
                   not move.isCastlingMove() &&
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::None;
        }));

        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::d3 &&
                   move.getTo() == Square::b2 &&
                   move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::BlackKnight &&
                   not move.isDoublePawnPush() &&
                   not move.isCastlingMove() &&
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::None;
        }));

        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::d3 &&
                   move.getTo() == Square::b4 &&
                   move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::BlackKnight &&
                   not move.isDoublePawnPush() &&
                   not move.isCastlingMove() &&
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::None;
        }));

        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::d3 &&
                   move.getTo() == Square::c5 &&
                   move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::BlackKnight &&
                   not move.isDoublePawnPush() &&
                   not move.isCastlingMove() &&
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::None;
        }));

        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::d3 &&
                   move.getTo() == Square::e5 &&
                   move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::BlackKnight &&
                   not move.isDoublePawnPush() &&
                   not move.isCastlingMove() &&
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::None;
        }));

        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::d3 &&
                   move.getTo() == Square::f4 &&
                   move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::BlackKnight &&
                   not move.isDoublePawnPush() &&
                   not move.isCastlingMove() &&
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::None;
        }));

        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::d3 &&
                   move.getTo() == Square::f2 &&
                   move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::BlackKnight &&
                   not move.isDoublePawnPush() &&
                   not move.isCastlingMove() &&
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::None;
        }));

        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::d3 &&
                   move.getTo() == Square::e1 &&
                   move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::BlackKnight &&
                   not move.isDoublePawnPush() &&
                   not move.isCastlingMove() &&
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::None;
        }));

        std::cout << generatedMoves << std::endl;
    }

    TEST(MoveGenerationTest, BlackKingAndQueenSideCastleTest)
    {
        /*
         * 8 ♖ . . . ♔ . . ♖
         * 7 . . . . ♙ . . .
         * 6 . . . . . . . .
         * 5 . . . . ♜ . . .
         * 4 . . . . . . . .
         * 3 . . . . . . . .
         * 2 . . . . . . . .
         * 1 . . . . ♚ . . .
         *
         *   a b c d e f g h
         */
        constexpr auto kingSideCastlingPosition = "r3k2r/4p3/8/4R3/8/8/8/4K3 b kq - 0 1";

        FenParsing::FenParser fenParser;
        const GameState gameState = fenParser.parse(kingSideCastlingPosition);

        std::vector<Move> generatedMoves;
        generatedMoves.reserve(16);

        MoveGeneration::generateBlackFigureMoves(gameState, generatedMoves);

        // King side castling - King Move
        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::e8 &&
                   move.getTo() == Square::g8 &&
                   not move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::BlackKing &&
                   not move.isDoublePawnPush() &&
                   move.isCastlingMove() &&
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::None;
        }));

        // King side castling - Rook Move
        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::h8 &&
                   move.getTo() == Square::f8 &&
                   not move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::BlackRook &&
                   not move.isDoublePawnPush() &&
                   not move.isCastlingMove() && // It's not added as castle move, but as natural move
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::None;
        }));

        // Queen side castling - King Move
        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::e8 &&
                   move.getTo() == Square::c8 &&
                   not move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::BlackKing &&
                   not move.isDoublePawnPush() &&
                   move.isCastlingMove() &&
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::None;
        }));

        // Queen side castling - Rook Move
        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::a8 &&
                   move.getTo() == Square::d8 &&
                   not move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::BlackRook &&
                   not move.isDoublePawnPush() &&
                   not move.isCastlingMove() && // It's not added as castle move, but as natural move
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::None;
        }));

        std::cout << generatedMoves << std::endl;
    }

    TEST(MoveGenerationTest, BlackKingCanCaptureTest)
    {
        /*
         * 8 . . . . . . . .
         * 7 . . . . . . . .
         * 6 . . ♟︎ ♟︎ ♟︎ . . .
         * 5 . . ♟︎ ♔ ♟︎ . . .
         * 4 . . ♟︎ ♟︎ ♟︎ . . .
         * 3 . . . . . . . .
         * 2 . . . . . . . .
         * 1 . . . ♚ . . . .
         *
         *   a b c d e f g h
         */
        constexpr auto kingSideCastlingPosition = "8/8/2PPP3/2PkP3/2PPP3/8/8/3K4 b - - 0 1";

        FenParsing::FenParser fenParser;
        const GameState gameState = fenParser.parse(kingSideCastlingPosition);

        std::vector<Move> generatedMoves;
        generatedMoves.reserve(16);

        MoveGeneration::generateBlackFigureMoves(gameState, generatedMoves);

        // King side castling - King Move
        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::d5 &&
                   move.getTo() == Square::c6 &&
                   move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::BlackKing &&
                   not move.isDoublePawnPush() &&
                    not move.isCastlingMove() &&
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::None;
        }));

        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::d5 &&
                   move.getTo() == Square::d6 &&
                   move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::BlackKing &&
                   not move.isDoublePawnPush() &&
                   not move.isCastlingMove() &&
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::None;
        }));

        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::d5 &&
                   move.getTo() == Square::e6 &&
                   move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::BlackKing &&
                   not move.isDoublePawnPush() &&
                   not move.isCastlingMove() &&
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::None;
        }));

        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::d5 &&
                   move.getTo() == Square::c5 &&
                   move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::BlackKing &&
                   not move.isDoublePawnPush() &&
                   not move.isCastlingMove() &&
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::None;
        }));

        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::d5 &&
                   move.getTo() == Square::c4 &&
                   move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::BlackKing &&
                   not move.isDoublePawnPush() &&
                   not move.isCastlingMove() &&
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::None;
        }));

        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::d5 &&
                   move.getTo() == Square::d4 &&
                   move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::BlackKing &&
                   not move.isDoublePawnPush() &&
                   not move.isCastlingMove() &&
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::None;
        }));

        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::d5 &&
                   move.getTo() == Square::e4 &&
                   move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::BlackKing &&
                   not move.isDoublePawnPush() &&
                   not move.isCastlingMove() &&
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::None;
        }));

        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::d5 &&
                   move.getTo() == Square::e5 &&
                   move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::BlackKing &&
                   not move.isDoublePawnPush() &&
                   not move.isCastlingMove() &&
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::None;
        }));

        std::cout << generatedMoves << std::endl;
    }

    TEST(MoveGenerationTest, EnPassantCaptureWithWhiteTest)
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
        FenParsing::FenParser fenParser;
        const GameState gameState = fenParser.parse(enPassantPosition);

        std::vector<Move> generatedMoves;
        generatedMoves.reserve(16);

        MoveGeneration::generateWhiteFigureMoves(gameState, generatedMoves);

        // En passant capture
        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::e5 &&
                   move.getTo() == Square::f6 &&
                   move.isCapture() &&
                   move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::WhitePawn &&
                   not move.isDoublePawnPush() &&
                   not move.isCastlingMove() &&
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::None;
        }));

        // Non-en passant capture
        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::e5 &&
                   move.getTo() == Square::e6 &&
                   not move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::WhitePawn &&
                   not move.isDoublePawnPush() &&
                   not move.isCastlingMove() &&
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::None;
        }));

        std::cout << generatedMoves << std::endl;
    }

    TEST(MoveGenerationTest, WhiteKingAndQueenSideCastleTest)
    {
        /*
         * 8 . . . . ♔ . . .
         * 7 . . . . . . . .
         * 6 . . . . . . . .
         * 5 . . . . . . . .
         * 4 . . . . ♖ . . .
         * 3 . . . . ♟︎ . . .
         * 2 . . . . . . . .
         * 1 ♜ . . . ♚ . . ♜
         *
         *  a b c d e f g h
         */
        constexpr auto kingSideCastlingPosition = "4k3/8/8/8/4r3/4P3/8/R3K2R w KQ - 0 1";

        FenParsing::FenParser fenParser;
        const GameState gameState = fenParser.parse(kingSideCastlingPosition);

        std::vector<Move> generatedMoves;
        generatedMoves.reserve(16);

        MoveGeneration::generateWhiteFigureMoves(gameState, generatedMoves);

        // King side castling - King Move
        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::e1 &&
                   move.getTo() == Square::g1 &&
                   not move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::WhiteKing &&
                   not move.isDoublePawnPush() &&
                   move.isCastlingMove() &&
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::None;
        }));

        // King side castling - Rook Move
        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::h1 &&
                   move.getTo() == Square::f1 &&
                   not move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::WhiteRook &&
                   not move.isDoublePawnPush() &&
                   not move.isCastlingMove() && // It's not added as castle move, but as natural move
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::None;
        }));

        // Queen side castling - King Move
        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::e1 &&
                   move.getTo() == Square::c1 &&
                   not move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::WhiteKing &&
                   not move.isDoublePawnPush() &&
                   move.isCastlingMove() &&
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::None;
        }));

        // Queen side castling - Rook Move
        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::a1 &&
                   move.getTo() == Square::d1 &&
                   not move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::WhiteRook &&
                   not move.isDoublePawnPush() &&
                   not move.isCastlingMove() && // It's not added as castle move, but as natural move
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::None;
        }));

        std::cout << generatedMoves << std::endl;
    }

    TEST(MoveGenerationTest, WhiteCanNotCastleKingAndQueenSideTest)
    {
        /*
         * 8 . . . . ♔ . . .
         * 7 . . . . . . . .
         * 6 . . . . . . . .
         * 5 . . . . . . . .
         * 4 . . . . ♖ . . .  // Rook attacking white king
         * 3 . . . . . . . .
         * 2 . . . . . . . .
         * 1 ♜ . . . ♚ . . ♜
         *
         *   a b c d e f g h
         */
        constexpr auto kingSideCastlingPosition = "4k3/8/8/8/4r3/8/8/R3K2R w KQ - 0 1";

        FenParsing::FenParser fenParser;
        const GameState gameState = fenParser.parse(kingSideCastlingPosition);

        std::vector<Move> generatedMoves;
        generatedMoves.reserve(16);

        MoveGeneration::generateWhiteFigureMoves(gameState, generatedMoves);

        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return not move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   not move.isDoublePawnPush() &&
                   not move.isCastlingMove() &&
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::None;
        }));

        std::cout << generatedMoves << std::endl;
    }

    TEST(MoveGenerationTest, DoublePawnPushWithWhiteTest)
    {
        /*
         * 8 . . . . ♔ . . .
         * 7 . . . . . . . .
         * 6 . . . . . . . .
         * 5 . . . . . . . .
         * 4 . . . . . . . .
         * 3 . . . . . . . .
         * 2 . . . . ♟︎ . . .
         * 1 ♜ . . . ♚ . . ♜
         *
         *   a b c d e f g h
         */
        constexpr auto kingSideCastlingPosition = "4k3/8/8/8/8/8/4P3/R3K2R w KQ - 0 1";

        FenParsing::FenParser fenParser;
        const GameState gameState = fenParser.parse(kingSideCastlingPosition);

        std::vector<Move> generatedMoves;
        generatedMoves.reserve(16);

        MoveGeneration::generateWhiteFigureMoves(gameState, generatedMoves);

        // Single pawn push
        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::e2 &&
                   move.getTo() == Square::e3 &&
                   not move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::WhitePawn &&
                   not move.isDoublePawnPush() &&
                   not move.isCastlingMove() &&
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::None;
        }));

        // Double pawn push
        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::e2 &&
                   move.getTo() == Square::e4 &&
                   not move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::WhitePawn &&
                   move.isDoublePawnPush() &&
                   not move.isCastlingMove() &&
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::None;
        }));

        std::cout << generatedMoves << std::endl;
    }

    TEST(MoveGenerationTest, PawnPromotionWithCaptureWithWhiteTest)
    {
        /*
         *   8 ♖ . ♖ . ♔ . . .
         *   7 . ♟︎ . . . . . .
         *   6 . . . . . . . .
         *   5 . . . . . . . .
         *   4 . . . . . . . .
         *   3 . . . . . . . .
         *   2 . . . ♚ . . . .
         *   1 . . . . . . . .
         *
         *     a b c d e f g h
         */
        constexpr auto kingSideCastlingPosition = "r1r1k3/1P6/8/8/8/8/3K4/8 w - - 0 1";

        FenParsing::FenParser fenParser;
        const GameState gameState = fenParser.parse(kingSideCastlingPosition);

        std::vector<Move> generatedMoves;
        generatedMoves.reserve(16);

        MoveGeneration::generateWhiteFigureMoves(gameState, generatedMoves);

        // to b8 - White Queen promotion
        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::b7 &&
                   move.getTo() == Square::b8 &&
                   not move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::WhitePawn &&
                   not move.isDoublePawnPush() &&
                   not move.isCastlingMove() &&
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::WhiteQueen;
        }));

        // to b8 - White Rook promotion
        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::b7 &&
                   move.getTo() == Square::b8 &&
                   not move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::WhitePawn &&
                   not move.isDoublePawnPush() &&
                   not move.isCastlingMove() &&
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::WhiteRook;
        }));

        // to b8 - White Bishop promotion
        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::b7 &&
                   move.getTo() == Square::b8 &&
                   not move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::WhitePawn &&
                   not move.isDoublePawnPush() &&
                   not move.isCastlingMove() &&
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::WhiteBishop;
        }));

        // to b8 - White Knight promotion
        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::b7 &&
                   move.getTo() == Square::b8 &&
                   not move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::WhitePawn &&
                   not move.isDoublePawnPush() &&
                   not move.isCastlingMove() &&
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::WhiteKnight;
        }));

        // to a8 - White Queen promotion with capture
        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::b7 &&
                   move.getTo() == Square::a8 &&
                   move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::WhitePawn &&
                   not move.isDoublePawnPush() &&
                   not move.isCastlingMove() &&
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::WhiteQueen;
        }));

        // to a8 - White Rook promotion with capture
        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::b7 &&
                   move.getTo() == Square::a8 &&
                   move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::WhitePawn &&
                   not move.isDoublePawnPush() &&
                   not move.isCastlingMove() &&
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::WhiteRook;
        }));

        // to a8 - White Bishop promotion with capture
        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::b7 &&
                   move.getTo() == Square::a8 &&
                   move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::WhitePawn &&
                   not move.isDoublePawnPush() &&
                   not move.isCastlingMove() &&
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::WhiteBishop;
        }));

        // to a8 - White Knight promotion with capture
        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::b7 &&
                   move.getTo() == Square::a8 &&
                   move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::WhitePawn &&
                   not move.isDoublePawnPush() &&
                   not move.isCastlingMove() &&
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::WhiteKnight;
        }));

        // to c8 - White Queen promotion with capture
        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::b7 &&
                   move.getTo() == Square::c8 &&
                   move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::WhitePawn &&
                   not move.isDoublePawnPush() &&
                   not move.isCastlingMove() &&
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::WhiteQueen;
        }));

        // to c8 - White Rook promotion with capture
        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::b7 &&
                   move.getTo() == Square::c8 &&
                   move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::WhitePawn &&
                   not move.isDoublePawnPush() &&
                   not move.isCastlingMove() &&
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::WhiteRook;
        }));

        // to c8 - White Bishop promotion with capture
        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::b7 &&
                   move.getTo() == Square::c8 &&
                   move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::WhitePawn &&
                   not move.isDoublePawnPush() &&
                   not move.isCastlingMove() &&
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::WhiteBishop;
        }));

        // to c8 - White Knight promotion with capture
        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::b7 &&
                   move.getTo() == Square::c8 &&
                   move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::WhitePawn &&
                   not move.isDoublePawnPush() &&
                   not move.isCastlingMove() &&
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::WhiteKnight;
        }));

        std::cout << generatedMoves << std::endl;
    }

    TEST(MoveGenerationTest, BishopCapturesTest)
    {
        /*
         *   8 . . . . ♔ . . .
         *   7 ♙ . . . . . ♙ .
         *   6 . . . . . . . .
         *   5 . . . . . . . .
         *   4 . . . ♝ . . . .
         *   3 . . . . . . . .
         *   2 . . . ♚ . . . .
         *   1 ♖ . . . . . ♖ .
         *
         *     a b c d e f g h
         */
        constexpr auto kingSideCastlingPosition = "4k3/p5p1/8/8/3B4/8/3K4/r5r1 w KQ - 0 1";

        FenParsing::FenParser fenParser;
        const GameState gameState = fenParser.parse(kingSideCastlingPosition);

        std::vector<Move> generatedMoves;
        generatedMoves.reserve(16);

        MoveGeneration::generateWhiteFigureMoves(gameState, generatedMoves);

        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::d4 &&
                   move.getTo() == Square::a7 &&
                   move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::WhiteBishop &&
                   not move.isDoublePawnPush() &&
                   not move.isCastlingMove() &&
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::None;
        }));

        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::d4 &&
                   move.getTo() == Square::a1 &&
                   move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::WhiteBishop &&
                   not move.isDoublePawnPush() &&
                   not move.isCastlingMove() &&
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::None;
        }));

        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::d4 &&
                   move.getTo() == Square::g1 &&
                   move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::WhiteBishop &&
                   not move.isDoublePawnPush() &&
                   not move.isCastlingMove() &&
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::None;
        }));

        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return move.getFrom() == Square::d4 &&
                   move.getTo() == Square::g7 &&
                   move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   move.getMovedFigure() == Figure::WhiteBishop &&
                   not move.isDoublePawnPush() &&
                   not move.isCastlingMove() &&
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::None;
        }));

        std::cout << generatedMoves << std::endl;
    }
}