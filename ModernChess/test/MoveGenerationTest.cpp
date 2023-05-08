#include "ModernChess/FenParsing.h"
#include "ModernChess/MoveGeneration.h"
#include "ModernChess/Utilities.h"

#include <gtest/gtest.h>

#include <algorithm>

using namespace ModernChess;
using namespace ModernChess::MoveGenerations;

namespace
{
    TEST(MoveGenerationTest, EnPassantTest)
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

        std::cout << generatedMoves;
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

        std::cout << generatedMoves;
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

        // King side castling - King Move
        EXPECT_TRUE(std::any_of(generatedMoves.begin(), generatedMoves.end(), [](const Move move) {
            return not move.isCapture() &&
                   not move.isEnPassantCapture() &&
                   not move.isDoublePawnPush() &&
                   not move.isCastlingMove() &&
                   not move.isNullMove() &&
                   move.getPromotedPiece() == Figure::None;
        }));

        std::cout << generatedMoves;
    }
}