#include "ModernChess/FenParsing.h"
#include "ModernChess/BitBoardOperations.h"

#include <gtest/gtest.h>

using namespace ModernChess;

namespace
{
    TEST(FenParsingTest, Init)
    {
        FenParsing::FenParser fenParser;
        const GameState gameState = fenParser.parse(FenParsing::startPosition);

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

        // Test occupation of white knights
        const BitBoardState whiteKnightsBitboard = gameState.board.bitboards[ColoredFigureType::WhiteKnight];
        EXPECT_TRUE(BitBoardOperations::isOccupied(whiteKnightsBitboard, Square::b1));
        EXPECT_TRUE(BitBoardOperations::isOccupied(whiteKnightsBitboard, Square::g1));

        // Test occupation of white bishops
        const BitBoardState whiteBishopsBitboard = gameState.board.bitboards[ColoredFigureType::WhiteBishop];
        EXPECT_TRUE(BitBoardOperations::isOccupied(whiteBishopsBitboard, Square::c1));
        EXPECT_TRUE(BitBoardOperations::isOccupied(whiteBishopsBitboard, Square::f1));

        // Test occupation of white king
        const BitBoardState whiteKingBitboard = gameState.board.bitboards[ColoredFigureType::WhiteKing];
        EXPECT_TRUE(BitBoardOperations::isOccupied(whiteKingBitboard, Square::e1));

        // Test occupation of white queen
        const BitBoardState whiteQueenBitboard = gameState.board.bitboards[ColoredFigureType::WhiteQueen];
        EXPECT_TRUE(BitBoardOperations::isOccupied(whiteQueenBitboard, Square::d1));

        // Test occupation of black pawns
        const BitBoardState blackPawnsBitboard = gameState.board.bitboards[ColoredFigureType::BlackPawn];

        for (Square square = Square::a7; square <= Square::h7; ++square)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(blackPawnsBitboard, square));
        }

        // Test occupation of black rooks
        const BitBoardState blackRooksBitboard = gameState.board.bitboards[ColoredFigureType::BlackRook];
        EXPECT_TRUE(BitBoardOperations::isOccupied(blackRooksBitboard, Square::a8));
        EXPECT_TRUE(BitBoardOperations::isOccupied(blackRooksBitboard, Square::h8));

        // Test occupation of black knights
        const BitBoardState blackKnightsBitboard = gameState.board.bitboards[ColoredFigureType::BlackKnight];
        EXPECT_TRUE(BitBoardOperations::isOccupied(blackKnightsBitboard, Square::b8));
        EXPECT_TRUE(BitBoardOperations::isOccupied(blackKnightsBitboard, Square::g8));

        // Test occupation of black bishops
        const BitBoardState blackBishopsBitboard = gameState.board.bitboards[ColoredFigureType::BlackBishop];
        EXPECT_TRUE(BitBoardOperations::isOccupied(blackBishopsBitboard, Square::c8));
        EXPECT_TRUE(BitBoardOperations::isOccupied(blackBishopsBitboard, Square::f8));

        // Test occupation of black queen
        const BitBoardState blackQueenBitboard = gameState.board.bitboards[ColoredFigureType::BlackQueen];
        EXPECT_TRUE(BitBoardOperations::isOccupied(blackQueenBitboard, Square::d8));

        // Test occupation of black king
        const BitBoardState blackKingBitboard = gameState.board.bitboards[ColoredFigureType::BlackKing];
        EXPECT_TRUE(BitBoardOperations::isOccupied(blackKingBitboard, Square::e8));

        EXPECT_TRUE(whiteCanKingSideCastle(gameState.castleRights));
        EXPECT_TRUE(whiteCanQueenSideCastle(gameState.castleRights));

        EXPECT_TRUE(blackCanKingSideCastle(gameState.castleRights));
        EXPECT_TRUE(blackCanQueenSideCastle(gameState.castleRights));

        EXPECT_EQ(gameState.enPassantTarget, Square::undefined);
        EXPECT_EQ(gameState.sideToMove, Color::White);
        EXPECT_EQ(gameState.halfMoveClock, 0);
        EXPECT_EQ(gameState.nextMoveClock, 1);

        std::cout << gameState;
    }

    TEST(FenParsingTest, BlackPawnAtA8)
    {
        constexpr auto fenString = "p7/8/8/8/8/8/8/8 w KQkq - 0 1";
        FenParsing::FenParser fenParser;
        const GameState gameState = fenParser.parse(fenString);

        const BitBoardState blackPawnsBitboard = gameState.board.bitboards[ColoredFigureType::BlackPawn];
        EXPECT_TRUE(BitBoardOperations::isOccupied(blackPawnsBitboard, Square::a8));

        std::cout << gameState;
    }
}