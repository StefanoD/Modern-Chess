#include "TestingPositions.h"

#include "ModernChess/MoveExecution.h"
#include "ModernChess/FenParsing.h"
#include "ModernChess/Utilities.h"

#include <gtest/gtest.h>

#include <algorithm>

using namespace ModernChess;
using namespace ModernChess::MoveGenerations;

namespace
{
    TEST(MoveExecutionTest, EnPassantCaptureWithWhite)
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
        GameState gameState = fenParser.parse();

        const Move move(Square::e5, Square::f6, Figure::WhitePawn, Figure::None, true, false, true, false);

        std::cout << "Before Move:" << std::endl;
        std::cout << gameState << std::endl << std::endl;

        const bool success = MoveExecution::executeMoveForWhite(gameState, move, MoveType::AllMoves);

        EXPECT_TRUE(success);
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::WhitePawn], Square::f6));
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.occupancies[Color::White], Square::f6));
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.occupancies[Color::Both], Square::f6));
        EXPECT_FALSE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::WhitePawn], Square::e5));
        EXPECT_FALSE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::BlackPawn], Square::f6));
        EXPECT_FALSE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::BlackPawn], Square::f5));
        EXPECT_EQ(gameState.board.sideToMove, Color::Black);

        std::cout << "After Move:" << std::endl;
        std::cout << gameState << std::endl;
    }

    TEST(MoveExecutionTest, EnPassantCaptureWithBlack)
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
        FenParsing::FenParser fenParser(enPassantPosition);
        GameState gameState = fenParser.parse();

        const Move move(Square::f4, Square::e3, Figure::BlackPawn, Figure::None, true, false, true, false);

        std::cout << "Before Move:" << std::endl;
        std::cout << gameState << std::endl << std::endl;

        const bool success = MoveExecution::executeMoveForBlack(gameState, move, MoveType::AllMoves);

        EXPECT_TRUE(success);
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::BlackPawn], Square::e3));
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.occupancies[Color::Black], Square::e3));
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.occupancies[Color::Both], Square::e3));
        EXPECT_FALSE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::BlackPawn], Square::f4));
        EXPECT_FALSE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::BlackPawn], Square::e4));
        EXPECT_FALSE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::WhitePawn], Square::e4));
        EXPECT_FALSE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::WhitePawn], Square::e3));
        EXPECT_EQ(gameState.board.sideToMove, Color::White);

        std::cout << "After Move:" << std::endl;
        std::cout << gameState << std::endl;
    }

    TEST(MoveExecutionTest, WhiteKingSideCastle)
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
         *   a b c d e f g h
         */
        constexpr auto kingSideCastlingPosition = "4k3/8/8/8/4r3/4P3/8/R3K2R w KQ - 0 1";
        FenParsing::FenParser fenParser(kingSideCastlingPosition);
        GameState gameState = fenParser.parse();

        const Move move(Square::e1, Square::g1, Figure::WhiteKing, Figure::None, false, false, false, true);

        std::cout << "Before Move:" << std::endl;
        std::cout << gameState << std::endl << std::endl;

        const bool success = MoveExecution::executeMoveForWhite(gameState, move, MoveType::AllMoves);

        EXPECT_TRUE(success);
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::WhiteKing], Square::g1));
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::WhiteRook], Square::f1));
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.occupancies[Color::White], Square::g1));
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.occupancies[Color::White], Square::f1));
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.occupancies[Color::Both], Square::g1));
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.occupancies[Color::Both], Square::f1));
        EXPECT_FALSE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::WhiteKing], Square::e1));
        EXPECT_FALSE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::WhiteRook], Square::h1));
        EXPECT_EQ(gameState.board.castlingRights, CastlingRights::Gone);
        EXPECT_EQ(gameState.board.sideToMove, Color::Black);

        std::cout << "After Move:" << std::endl;
        std::cout << gameState << std::endl;
    }

    TEST(MoveExecutionTest, WhitePosition2_d5e6_Capture)
    {
        /*
         * 8 ♖ . . . ♔ . . ♖
         * 7 ♙ . ♙ ♙ ♕ ♙ ♗ .
         * 6 ♗ ♘ . . ♙ ♘ ♙ .
         * 5 . . . ♟︎ ♞ . . .
         * 4 . ♙ . . ♟︎ . . .
         * 3 . . ♞ . . ♛ . ♙
         * 2 ♟︎ ♟︎ ♟︎ ♝ ♝ ♟︎ ♟︎ ♟︎
         * 1 ♜ . . . ♚ . . ♜
         *
         *   a b c d e f g h
         */
        FenParsing::FenParser fenParser(TestingPositions::Position2);
        GameState gameState = fenParser.parse();

        const Move move(Square::d5, Square::e6, Figure::WhitePawn, Figure::None, true, false, false, false);

        std::cout << "Before Move:" << std::endl;
        std::cout << gameState << std::endl << std::endl;

        const bool success = MoveExecution::executeMoveForWhite(gameState, move, MoveType::AllMoves);

        EXPECT_TRUE(success);
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::WhitePawn], Square::e6));
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.occupancies[Color::White], Square::e6));
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.occupancies[Color::Both], Square::e6));
        EXPECT_FALSE(BitBoardOperations::isOccupied(gameState.board.occupancies[Color::Black], Square::e6));
        EXPECT_FALSE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::BlackPawn], Square::e6));
        EXPECT_EQ(gameState.board.sideToMove, Color::Black);

        std::cout << "After Move:" << std::endl;
        std::cout << gameState << std::endl;
    }

    TEST(MoveExecutionTest, BlackKingSideCastle)
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

        FenParsing::FenParser fenParser(kingSideCastlingPosition);
        GameState gameState = fenParser.parse();

        const Move move(Square::e8, Square::g8, Figure::BlackKing, Figure::None, false, false, false, true);

        std::cout << "Before Move:" << std::endl;
        std::cout << gameState << std::endl << std::endl;

        const bool success = MoveExecution::executeMoveForBlack(gameState, move, MoveType::AllMoves);

        EXPECT_TRUE(success);
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::BlackKing], Square::g8));
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::BlackRook], Square::f8));
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.occupancies[Color::Black], Square::g8));
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.occupancies[Color::Black], Square::f8));
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.occupancies[Color::Both], Square::g8));
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.occupancies[Color::Both], Square::f8));
        EXPECT_FALSE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::BlackKing], Square::e8));
        EXPECT_FALSE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::BlackRook], Square::h8));
        EXPECT_EQ(gameState.board.castlingRights, CastlingRights::Gone);
        EXPECT_EQ(gameState.board.sideToMove, Color::White);

        std::cout << "After Move:" << std::endl;
        std::cout << gameState << std::endl;
    }

    TEST(MoveExecutionTest, WhiteQueenSideCastle)
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
         *   a b c d e f g h
         */
        constexpr auto kingSideCastlingPosition = "4k3/8/8/8/4r3/4P3/8/R3K2R w KQ - 0 1";
        FenParsing::FenParser fenParser(kingSideCastlingPosition);
        GameState gameState = fenParser.parse();

        const Move move(Square::e1, Square::c1, Figure::WhiteKing, Figure::None, false, false, false, true);

        std::cout << "Before Move:" << std::endl;
        std::cout << gameState << std::endl << std::endl;

        const bool success = MoveExecution::executeMoveForWhite(gameState, move, MoveType::AllMoves);

        EXPECT_TRUE(success);
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::WhiteKing], Square::c1));
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::WhiteRook], Square::d1));
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.occupancies[Color::White], Square::c1));
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.occupancies[Color::White], Square::d1));
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.occupancies[Color::Both], Square::c1));
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.occupancies[Color::Both], Square::d1));
        EXPECT_FALSE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::WhiteKing], Square::e1));
        EXPECT_FALSE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::WhiteRook], Square::a1));
        EXPECT_EQ(gameState.board.castlingRights, CastlingRights::Gone);
        EXPECT_EQ(gameState.board.sideToMove, Color::Black);

        std::cout << "After Move:" << std::endl;
        std::cout << gameState << std::endl;
    }

    TEST(MoveExecutionTest, BlackQueenSideCastle)
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

        FenParsing::FenParser fenParser(kingSideCastlingPosition);
        GameState gameState = fenParser.parse();

        const Move move(Square::e8, Square::c8, Figure::BlackKing, Figure::None, false, false, false, true);

        std::cout << "Before Move:" << std::endl;
        std::cout << gameState << std::endl << std::endl;

        const bool success = MoveExecution::executeMoveForBlack(gameState, move, MoveType::AllMoves);

        EXPECT_TRUE(success);
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::BlackKing], Square::c8));
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::BlackRook], Square::d8));
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.occupancies[Color::Black], Square::c8));
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.occupancies[Color::Black], Square::d8));
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.occupancies[Color::Both], Square::c8));
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.occupancies[Color::Both], Square::d8));
        EXPECT_FALSE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::BlackKing], Square::e8));
        EXPECT_FALSE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::BlackRook], Square::a8));
        EXPECT_EQ(gameState.board.castlingRights, CastlingRights::Gone);
        EXPECT_EQ(gameState.board.sideToMove, Color::White);

        std::cout << "After Move:" << std::endl;
        std::cout << gameState << std::endl;
    }

    TEST(MoveExecutionTest, WhiteCanNotCastleQueenSide)
    {
        /*
         * 8 . . . . ♔ . . .
         * 7 . . . . . . . .
         * 6 . . . . . . . .
         * 5 . . . . . . . .
         * 4 . . ♖ . . . . .  // Rook attacking white king when king castles queen side
         * 3 . . . . . . . .
         * 2 . . . . . . . .
         * 1 ♜ . . . ♚ . . ♜
         *
         *   a b c d e f g h
         */
        constexpr auto kingSideCastlingPosition = "4k3/8/8/8/2r5/8/8/R3K2R w KQ - 0 1";
        FenParsing::FenParser fenParser(kingSideCastlingPosition);
        GameState gameState = fenParser.parse();

        const Move move(Square::e1, Square::c1, Figure::WhiteKing, Figure::None, false, false, false, true);

        std::cout << "Before Move:" << std::endl;
        std::cout << gameState << std::endl << std::endl;

        const bool success = MoveExecution::executeMoveForWhite(gameState, move, MoveType::AllMoves);

        EXPECT_FALSE(success);
        EXPECT_FALSE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::WhiteKing], Square::c1));
        EXPECT_FALSE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::WhiteRook], Square::d1));
        EXPECT_FALSE(BitBoardOperations::isOccupied(gameState.board.occupancies[Color::White], Square::c1));
        EXPECT_FALSE(BitBoardOperations::isOccupied(gameState.board.occupancies[Color::White], Square::d1));
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::WhiteKing], Square::e1));
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::WhiteRook], Square::a1));
        EXPECT_EQ(gameState.board.castlingRights, CastlingRights::WhiteAnySide); // White has still castling rights
        EXPECT_EQ(gameState.board.sideToMove, Color::White); // White has still to move

        std::cout << "After Move:" << std::endl;
        std::cout << gameState << std::endl;
    }

    TEST(MoveExecutionTest, BlackCanNotCastleKingSide)
    {
        /*
         *  8 ♖ . . . ♔ . . ♖
         *  7 . . . . . . . .
         *  6 . . . . . . . .
         *  5 . . . . . . ♜ . // Rook attacking black king on king side castling
         *  4 . . . . . . . .
         *  3 . . . . . . . .
         *  2 . . . . . . . .
         *  1 . . . . ♚ . . .
         *
         *    a b c d e f g h
         *
         */
        constexpr auto kingSideCastlingPosition = "r3k2r/8/8/6R1/8/8/8/4K3 b kq - 0 1";
        FenParsing::FenParser fenParser(kingSideCastlingPosition);
        GameState gameState = fenParser.parse();

        const Move move(Square::e8, Square::g8, Figure::BlackKing, Figure::None, false, false, false, true);

        std::cout << "Before Move:" << std::endl;
        std::cout << gameState << std::endl << std::endl;

        const bool success = MoveExecution::executeMoveForBlack(gameState, move, MoveType::AllMoves);

        EXPECT_FALSE(success);
        EXPECT_FALSE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::BlackKing], Square::g8));
        EXPECT_FALSE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::BlackRook], Square::f8));
        EXPECT_FALSE(BitBoardOperations::isOccupied(gameState.board.occupancies[Color::Black], Square::g8));
        EXPECT_FALSE(BitBoardOperations::isOccupied(gameState.board.occupancies[Color::Black], Square::f8));
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::BlackKing], Square::e8));
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::BlackRook], Square::a8));
        EXPECT_EQ(gameState.board.castlingRights, CastlingRights::BlackAnySide); // White has still castling rights
        EXPECT_EQ(gameState.board.sideToMove, Color::Black); // Black has still to move

        std::cout << "After Move:" << std::endl;
        std::cout << gameState << std::endl;
    }

    TEST(MoveExecutionTest, DoublePawnPushWithWhite)
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
        constexpr auto fenPosition = "4k3/8/8/8/8/8/4P3/R3K2R w KQ - 0 1";

        FenParsing::FenParser fenParser(fenPosition);
        GameState gameState = fenParser.parse();

        const Move move(Square::e2, Square::e4, Figure::WhitePawn, Figure::None, false, true, false, false);

        std::cout << "Before Move:" << std::endl;
        std::cout << gameState << std::endl << std::endl;

        const bool success = MoveExecution::executeMoveForWhite(gameState, move, MoveType::AllMoves);

        EXPECT_TRUE(success);
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::WhitePawn], Square::e4));
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.occupancies[Color::White], Square::e4));
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.occupancies[Color::Both], Square::e4));
        EXPECT_FALSE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::WhitePawn], Square::e2));
        EXPECT_EQ(gameState.board.enPassantTarget, Square::e3);
        EXPECT_EQ(gameState.board.sideToMove, Color::Black);

        std::cout << "After Move:" << std::endl;
        std::cout << gameState << std::endl;
    }

    TEST(MoveExecutionTest, DoublePawnPushWithBlack)
    {
        /*
         * 8 . . . . ♔ . . .
         * 7 . . . . ♙ . . .
         * 6 . . . . . . . .
         * 5 . . . . . . . .
         * 4 . . . . . . . .
         * 3 . . . . . . . .
         * 2 . . . . . . . .
         * 1 . . . . ♚ . . .
         *
         *   a b c d e f g h
         */
        constexpr auto fenPosition = "4k3/4p3/8/8/8/8/8/4K3 b - - 0 1";

        FenParsing::FenParser fenParser(fenPosition);
        GameState gameState = fenParser.parse();

        const Move move(Square::e7, Square::e5, Figure::BlackPawn, Figure::None, false, true, false, false);

        std::cout << "Before Move:" << std::endl;
        std::cout << gameState << std::endl << std::endl;

        const bool success = MoveExecution::executeMoveForBlack(gameState, move, MoveType::AllMoves);

        EXPECT_TRUE(success);
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::BlackPawn], Square::e5));
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.occupancies[Color::Black], Square::e5));
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.occupancies[Color::Both], Square::e5));
        EXPECT_FALSE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::BlackPawn], Square::e7));
        EXPECT_EQ(gameState.board.enPassantTarget, Square::e6);
        EXPECT_EQ(gameState.board.sideToMove, Color::White);

        std::cout << "After Move:" << std::endl;
        std::cout << gameState << std::endl;
    }

    TEST(MoveExecutionTest, PawnPromotionWithCaptureWithWhite)
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
        constexpr auto fenPosition = "r1r1k3/1P6/8/8/8/8/3K4/8 w - - 0 1";

        FenParsing::FenParser fenParser(fenPosition);
        GameState gameState = fenParser.parse();

        const Move move(Square::b7, Square::c8, Figure::WhitePawn, Figure::WhiteQueen, true, false, false, false);

        std::cout << "Before Move:" << std::endl;
        std::cout << gameState << std::endl << std::endl;

        const bool success = MoveExecution::executeMoveForWhite(gameState, move, MoveType::AllMoves);

        EXPECT_TRUE(success);
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::WhiteQueen], Square::c8));
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.occupancies[Color::White], Square::c8));
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.occupancies[Color::Both], Square::c8));
        EXPECT_FALSE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::WhitePawn], Square::b7));
        EXPECT_FALSE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::WhitePawn], Square::c8));
        EXPECT_FALSE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::BlackRook], Square::c8));
        EXPECT_FALSE(BitBoardOperations::isOccupied(gameState.board.occupancies[Color::Black], Square::c8));
        EXPECT_EQ(gameState.board.sideToMove, Color::Black);

        std::cout << "After Move:" << std::endl;
        std::cout << gameState << std::endl;
    }

    TEST(MoveExecutionTest, PawnPromotionWithCaptureWithBlack)
    {
        /*
         * 8 . . . . ♔ . . .
         * 7 . . . . . . . .
         * 6 . . . . . . . .
         * 5 . . . . . . . .
         * 4 . . . . . . . .
         * 3 . . . . . . . .
         * 2 . ♙ . . . . . .
         * 1 . . ♜ . ♚ . . .
         *
         *   a b c d e f g h
         */
        constexpr auto fenPosition = "4k3/8/8/8/8/8/1p6/2R1K3 b - - 0 1";

        FenParsing::FenParser fenParser(fenPosition);
        GameState gameState = fenParser.parse();

        const Move move(Square::b2, Square::c1, Figure::BlackPawn, Figure::BlackQueen, true, false, false, false);

        std::cout << "Before Move:" << std::endl;
        std::cout << gameState << std::endl << std::endl;

        const bool success = MoveExecution::executeMoveForBlack(gameState, move, MoveType::AllMoves);

        EXPECT_TRUE(success);
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::BlackQueen], Square::c1));
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.occupancies[Color::Black], Square::c1));
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.occupancies[Color::Both], Square::c1));
        EXPECT_FALSE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::BlackPawn], Square::b2));
        EXPECT_FALSE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::BlackPawn], Square::c1));
        EXPECT_FALSE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::WhiteRook], Square::c1));
        EXPECT_EQ(gameState.board.sideToMove, Color::White);

        std::cout << "After Move:" << std::endl;
        std::cout << gameState << std::endl;
    }

    TEST(MoveExecutionTest, PawnPushWithBlack)
    {
        /*
         * 8 ♖ ♘ ♗ ♕ ♔ ♗ . ♖
         * 7 ♙ ♙ ♙ ♙ . ♙ ♙ ♙
         * 6 . . . . . ♘ . .
         * 5 . . . . ♙ . . .  // Black & White are position equalizing to 0
         * 4 . . . . ♟︎ . . .
         * 3 . . . . . ♞ . . // New knight position counts 20
         * 2 ♟︎ ♟︎ ♟︎ ♟︎ . ♟︎ ♟︎ ♟︎
         * 1 ♜ ♞ ♝ ♛ ♚ ♝ . ♜ // This empty square counts -10
         *
         *   a b c d e f g h
         */
        FenParsing::FenParser fenParser("rnbqkb1r/pppp1ppp/5n2/4p3/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq - 0 1");
        GameState gameState = fenParser.parse();

        const Move move(Square::a7, Square::a6, Figure::BlackPawn, Figure::None, false, false, false, false);

        const bool success = MoveExecution::executeMoveForBlack(gameState, move, MoveType::AllMoves);
        EXPECT_TRUE(success);
        std::cout << gameState;
    }
}