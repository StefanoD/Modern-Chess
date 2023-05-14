#include "ModernChess/MoveExecution.h"
#include "ModernChess/FenParsing.h"
#include "ModernChess/Utilities.h"

#include <gtest/gtest.h>

#include <algorithm>

using namespace ModernChess;
using namespace ModernChess::MoveGenerations;

namespace
{
    TEST(MoveExecutionTest, EnPassantCaptureWithWhiteTest)
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
        GameState gameState = fenParser.parse(enPassantPosition);

        const Move move(Square::e5, Square::f6, Figure::WhitePawn, Figure::None, true, false, true, false);

        std::cout << "Before Move:" << std::endl;
        std::cout << gameState << std::endl << std::endl;

        const bool success = MoveExecution::executeMoveForWhite(gameState, move, MoveType::AllMoves);

        EXPECT_TRUE(success);
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::WhitePawn], Square::f6));
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.occupancies[Color::White], Square::f6));
        EXPECT_FALSE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::WhitePawn], Square::e5));
        EXPECT_FALSE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::BlackPawn], Square::f6));
        EXPECT_FALSE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::BlackPawn], Square::f5));

        std::cout << "After Move:" << std::endl;
        std::cout << gameState << std::endl;
    }


}