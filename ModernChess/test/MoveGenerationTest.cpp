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

    TEST(MoveGenerationTest, WhiteKindSideCastleTest)
    {
        constexpr auto kingSideCastlingPosition = "rnbqkbnr/pppppppp/8/8/8/4PN2/PPPPBPPP/RNBQK2R w KQkq - 0 1";

        FenParsing::FenParser fenParser;
        const GameState gameState = fenParser.parse(kingSideCastlingPosition);

        std::vector<Move> generatedMoves;
        generatedMoves.reserve(16);

        MoveGeneration::generateWhiteFigureMoves(gameState, generatedMoves);

        std::cout << generatedMoves;
    }
}