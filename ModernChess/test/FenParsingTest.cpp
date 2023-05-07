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
        const BitBoardState whitePawnsBitboard = gameState.board.bitboards[Figure::WhitePawn];

        for (Square square = Square::a2; square <= Square::h2; ++square)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(whitePawnsBitboard, square));
        }

        // Test occupation of white rooks
        const BitBoardState whiteRooksBitboard = gameState.board.bitboards[Figure::WhiteRook];
        EXPECT_TRUE(BitBoardOperations::isOccupied(whiteRooksBitboard, Square::a1));
        EXPECT_TRUE(BitBoardOperations::isOccupied(whiteRooksBitboard, Square::h1));

        // Test occupation of white knights
        const BitBoardState whiteKnightsBitboard = gameState.board.bitboards[Figure::WhiteKnight];
        EXPECT_TRUE(BitBoardOperations::isOccupied(whiteKnightsBitboard, Square::b1));
        EXPECT_TRUE(BitBoardOperations::isOccupied(whiteKnightsBitboard, Square::g1));

        // Test occupation of white bishops
        const BitBoardState whiteBishopsBitboard = gameState.board.bitboards[Figure::WhiteBishop];
        EXPECT_TRUE(BitBoardOperations::isOccupied(whiteBishopsBitboard, Square::c1));
        EXPECT_TRUE(BitBoardOperations::isOccupied(whiteBishopsBitboard, Square::f1));

        // Test occupation of white king
        const BitBoardState whiteKingBitboard = gameState.board.bitboards[Figure::WhiteKing];
        EXPECT_TRUE(BitBoardOperations::isOccupied(whiteKingBitboard, Square::e1));

        // Test occupation of white queen
        const BitBoardState whiteQueenBitboard = gameState.board.bitboards[Figure::WhiteQueen];
        EXPECT_TRUE(BitBoardOperations::isOccupied(whiteQueenBitboard, Square::d1));

        // Test occupation of black pawns
        const BitBoardState blackPawnsBitboard = gameState.board.bitboards[Figure::BlackPawn];

        for (Square square = Square::a7; square <= Square::h7; ++square)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(blackPawnsBitboard, square));
        }

        // Test occupation of black rooks
        const BitBoardState blackRooksBitboard = gameState.board.bitboards[Figure::BlackRook];
        EXPECT_TRUE(BitBoardOperations::isOccupied(blackRooksBitboard, Square::a8));
        EXPECT_TRUE(BitBoardOperations::isOccupied(blackRooksBitboard, Square::h8));

        // Test occupation of black knights
        const BitBoardState blackKnightsBitboard = gameState.board.bitboards[Figure::BlackKnight];
        EXPECT_TRUE(BitBoardOperations::isOccupied(blackKnightsBitboard, Square::b8));
        EXPECT_TRUE(BitBoardOperations::isOccupied(blackKnightsBitboard, Square::g8));

        // Test occupation of black bishops
        const BitBoardState blackBishopsBitboard = gameState.board.bitboards[Figure::BlackBishop];
        EXPECT_TRUE(BitBoardOperations::isOccupied(blackBishopsBitboard, Square::c8));
        EXPECT_TRUE(BitBoardOperations::isOccupied(blackBishopsBitboard, Square::f8));

        // Test occupation of black queen
        const BitBoardState blackQueenBitboard = gameState.board.bitboards[Figure::BlackQueen];
        EXPECT_TRUE(BitBoardOperations::isOccupied(blackQueenBitboard, Square::d8));

        // Test occupation of black king
        const BitBoardState blackKingBitboard = gameState.board.bitboards[Figure::BlackKing];
        EXPECT_TRUE(BitBoardOperations::isOccupied(blackKingBitboard, Square::e8));

        EXPECT_TRUE(whiteCanCastleKingSide(gameState.castleRights));
        EXPECT_TRUE(whiteCanCastleQueenSide(gameState.castleRights));

        EXPECT_TRUE(blackCanCastleKingSide(gameState.castleRights));
        EXPECT_TRUE(blackCanCastleQueenSide(gameState.castleRights));

        EXPECT_EQ(gameState.enPassantTarget, Square::undefined);
        EXPECT_EQ(gameState.sideToMove, Color::White);
        EXPECT_EQ(gameState.halfMoveClock, 0);
        EXPECT_EQ(gameState.nextMoveClock, 1);

        std::cout << gameState;
    }

    TEST(FenParsingTest, ParseEnPassantSquare)
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

        EXPECT_EQ(gameState.enPassantTarget, Square::f6);
    }

    TEST(FenParsingTest, BlackPawnAtA8)
    {
        constexpr auto fenString = "p7/8/8/8/8/8/8/8 w KQkq - 0 1";
        FenParsing::FenParser fenParser;
        const GameState gameState = fenParser.parse(fenString);

        const BitBoardState blackPawnsBitboard = gameState.board.bitboards[Figure::BlackPawn];
        EXPECT_TRUE(BitBoardOperations::isOccupied(blackPawnsBitboard, Square::a8));

        std::stringstream streamPrintedBoard;
        streamPrintedBoard << gameState;

        const std::string printedBoard = streamPrintedBoard.str();

        // Make sure the black pawn is printed on the correct position,
        // and it is really a black pawn and not a white pawn
        EXPECT_TRUE(printedBoard.find("8 ♙ . . . . . . .") != std::string::npos);

        std::cout << gameState;
    }

    TEST(FenParsingTest, TrickyPosition)
    {
        constexpr auto trickyPosition = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1";
        FenParsing::FenParser fenParser;
        const GameState gameState = fenParser.parse(trickyPosition);

        // Test occupation of black rooks
        const BitBoardState blackRooksBitboard = gameState.board.bitboards[Figure::BlackRook];
        EXPECT_TRUE(BitBoardOperations::isOccupied(blackRooksBitboard, Square::a8));
        EXPECT_TRUE(BitBoardOperations::isOccupied(blackRooksBitboard, Square::h8));

        // Test occupation of black king
        const BitBoardState blackKingBitboard = gameState.board.bitboards[Figure::BlackKing];
        EXPECT_TRUE(BitBoardOperations::isOccupied(blackKingBitboard, Square::e8));

        // Test occupation of black knights
        const BitBoardState blackKnightsBitboard = gameState.board.bitboards[Figure::BlackKnight];
        EXPECT_TRUE(BitBoardOperations::isOccupied(blackKnightsBitboard, Square::b6));
        EXPECT_TRUE(BitBoardOperations::isOccupied(blackKnightsBitboard, Square::f6));

        // Test occupation of black pawns
        const BitBoardState blackPawnsBitboard = gameState.board.bitboards[Figure::BlackPawn];
        EXPECT_TRUE(BitBoardOperations::isOccupied(blackPawnsBitboard, Square::a7));
        EXPECT_TRUE(BitBoardOperations::isOccupied(blackPawnsBitboard, Square::c7));
        EXPECT_TRUE(BitBoardOperations::isOccupied(blackPawnsBitboard, Square::d7));
        EXPECT_TRUE(BitBoardOperations::isOccupied(blackPawnsBitboard, Square::f7));

        // Test occupation of black queen
        const BitBoardState blackQueenBitboard = gameState.board.bitboards[Figure::BlackQueen];
        EXPECT_TRUE(BitBoardOperations::isOccupied(blackQueenBitboard, Square::e7));

        // Test occupation of black bishops
        const BitBoardState blackBishopsBitboard = gameState.board.bitboards[Figure::BlackBishop];
        EXPECT_TRUE(BitBoardOperations::isOccupied(blackBishopsBitboard, Square::g7));
        EXPECT_TRUE(BitBoardOperations::isOccupied(blackBishopsBitboard, Square::a6));

        // Test occupation of white pawns
        const BitBoardState whitePawnsBitboard = gameState.board.bitboards[Figure::WhitePawn];
        EXPECT_TRUE(BitBoardOperations::isOccupied(whitePawnsBitboard, Square::d5));
        EXPECT_TRUE(BitBoardOperations::isOccupied(whitePawnsBitboard, Square::e4));
        EXPECT_TRUE(BitBoardOperations::isOccupied(whitePawnsBitboard, Square::a2));
        EXPECT_TRUE(BitBoardOperations::isOccupied(whitePawnsBitboard, Square::b2));
        EXPECT_TRUE(BitBoardOperations::isOccupied(whitePawnsBitboard, Square::c2));
        EXPECT_TRUE(BitBoardOperations::isOccupied(whitePawnsBitboard, Square::f2));
        EXPECT_TRUE(BitBoardOperations::isOccupied(whitePawnsBitboard, Square::g2));
        EXPECT_TRUE(BitBoardOperations::isOccupied(whitePawnsBitboard, Square::h2));

        // Test occupation of white king
        const BitBoardState whiteKingBitboard = gameState.board.bitboards[Figure::WhiteKing];
        EXPECT_TRUE(BitBoardOperations::isOccupied(whiteKingBitboard, Square::e1));

        // Test occupation of white knights
        const BitBoardState whiteKnightsBitboard = gameState.board.bitboards[Figure::WhiteKnight];
        EXPECT_TRUE(BitBoardOperations::isOccupied(whiteKnightsBitboard, Square::c3));
        EXPECT_TRUE(BitBoardOperations::isOccupied(whiteKnightsBitboard, Square::e5));

        // Test occupation of white rooks
        const BitBoardState whiteRooksBitboard = gameState.board.bitboards[Figure::WhiteRook];
        EXPECT_TRUE(BitBoardOperations::isOccupied(whiteRooksBitboard, Square::a1));
        EXPECT_TRUE(BitBoardOperations::isOccupied(whiteRooksBitboard, Square::h1));

        std::stringstream streamPrintedBoard;
        streamPrintedBoard << gameState;

        const std::string printedBoard = streamPrintedBoard.str();

        // Test printed output
        EXPECT_TRUE(printedBoard.find("8 ♖ . . . ♔ . . ♖") != std::string::npos);
        EXPECT_TRUE(printedBoard.find("7 ♙ . ♙ ♙ ♕ ♙ ♗ .") != std::string::npos);
        EXPECT_TRUE(printedBoard.find("6 ♗ ♘ . . ♙ ♘ ♙ .") != std::string::npos);
        EXPECT_TRUE(printedBoard.find("5 . . . ♟\uFE0E ♞ . . .") != std::string::npos);
        EXPECT_TRUE(printedBoard.find("4 . ♙ . . ♟\uFE0E . . .") != std::string::npos);
        EXPECT_TRUE(printedBoard.find("3 . . ♞ . . ♛ . ♙") != std::string::npos);
        EXPECT_TRUE(printedBoard.find("2 ♟\uFE0E ♟\uFE0E ♟\uFE0E ♝ ♝ ♟\uFE0E ♟\uFE0E ♟\uFE0E") != std::string::npos);
        EXPECT_TRUE(printedBoard.find("1 ♜ . . . ♚ . . ♜") != std::string::npos);

        std::cout << gameState;
    }
}