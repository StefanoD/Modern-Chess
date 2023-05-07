#include "ModernChess/FenParsing.h"
#include "ModernChess/MoveGeneration.h"
#include "ModernChess/Utilities.h"

#include <gtest/gtest.h>

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

        print(std::cout, BitBoardOperations::occupySquare(BoardState::empty, Square::f6));
        print(std::cout, AttackQueries::pawnAttackTable[Color::White][Square::e5]);

        printAttackedSquares(std::cout, gameState.board, Color::White);

        MoveGeneration::generateWhiteFigureMoves(gameState, generatedMoves);

        std::cout << generatedMoves;
    }
}