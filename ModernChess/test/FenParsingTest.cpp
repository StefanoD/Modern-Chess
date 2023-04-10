#include "ModernChess/FenParsing.h"
#include "ModernChess/BitBoardOperations.h"

#include <gtest/gtest.h>

using namespace ModernChess;

namespace
{
    TEST(FenParsingTest, Init)
    {
        GameState gameState = FenParsing::parse(FenParsing::startPosition);
        //GameState gameState;

        const BitBoardState bitBoardState = gameState.board.getOccupiedSquares();

        // Test occupation of white pawns
        const BitBoardState whitePawnsBitboard = gameState.board.bitboards[ColoredFigureType::WhitePawn];

        for (Square square = Square::a2; square <= Square::h2; ++square)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(whitePawnsBitboard, square));
        }

        // Test occupation of white rooks
        const BitBoardState whiteRooksBitboard = gameState.board.bitboards[ColoredFigureType::WhiteRook];
        EXPECT_TRUE(BitBoardOperations::isOccupied(whiteRooksBitboard, Square::a1));
        EXPECT_TRUE(BitBoardOperations::isOccupied(whiteRooksBitboard, Square::h1));

        // Test occupation of white rooks
        const BitBoardState whiteKnightsBitboard = gameState.board.bitboards[ColoredFigureType::WhiteKnight];
        EXPECT_TRUE(BitBoardOperations::isOccupied(whiteKnightsBitboard, Square::b1));
        EXPECT_TRUE(BitBoardOperations::isOccupied(whiteKnightsBitboard, Square::g1));

        // Test if squares are not occupied
        for (Square square = Square::a3; square <= Square::h6; ++square)
        {
            EXPECT_FALSE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        // Test occupation of Black figures
        for (Square square = Square::a7; square <= Square::h8; ++square)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(bitBoardState, Square(square)));
        }

        std::cout << gameState;
    }
}