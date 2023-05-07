#include "ModernChess/Move.h"

#include <gtest/gtest.h>

#include <strstream>

using namespace ModernChess;

namespace {
    TEST(MoveTest, TestAllEncodings)
    {
        const std::vector<Figure> movedFigures{
                Figure::WhitePawn,
                Figure::WhiteKnight,
                Figure::WhiteBishop,
                Figure::WhiteRook,
                Figure::WhiteQueen,
                Figure::WhiteKing,
                Figure::BlackPawn,
                Figure::BlackKnight,
                Figure::BlackBishop,
                Figure::BlackRook,
                Figure::BlackQueen,
                Figure::BlackKing,
        };
        const std::vector<Figure> promotedPieces{
                Figure::WhiteKnight,
                Figure::WhiteBishop,
                Figure::WhiteRook,
                Figure::WhiteQueen,
                Figure::BlackKnight,
                Figure::BlackBishop,
                Figure::BlackRook,
                Figure::BlackQueen,
                Figure::None,
        };

        for (Square from = Square::a1; from <= Square::h8; ++from)
        {
            for (Square to = Square::a1; to <= Square::h8; ++to)
            {
                for (const Figure movedFigure: movedFigures)
                {
                    for (const Figure promotedPiece: promotedPieces)
                    {
                        for (uint8_t enPassant = 0; enPassant <= 1; ++enPassant)
                        {
                            for (uint8_t isCapture = 0; isCapture <= 1; ++isCapture)
                            {
                                for (uint8_t isCastling = 0; isCastling <= 1; ++isCastling)
                                {
                                    for (uint8_t isDoublePawnPush = 0; isDoublePawnPush <= 1; ++isDoublePawnPush)
                                    {
                                        const Move move(from,
                                                        to,
                                                        movedFigure,
                                                        promotedPiece,
                                                        bool(isCapture),
                                                        bool(isDoublePawnPush),
                                                        bool(enPassant),
                                                        bool(isCastling));
                                        EXPECT_EQ(move.getFrom(), from);
                                        EXPECT_EQ(move.getTo(), to);
                                        EXPECT_EQ(move.getMovedFigure(), movedFigure);
                                        EXPECT_EQ(move.getPromotedPiece(), promotedPiece);
                                        EXPECT_EQ(move.isCapture(), bool(isCapture));
                                        EXPECT_EQ(move.isDoublePawnPush(), bool(isDoublePawnPush));
                                        EXPECT_EQ(move.isEnPassantCapture(), bool(enPassant));
                                        EXPECT_EQ(move.isCastlingMove(), bool(isCastling));

                                        //std::cout << move << std::endl;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    TEST(MoveTest, TestUCIEncodedNullMovePrint)
    {
        const Move nullMove;

        std::stringstream stream;

        stream << nullMove;

        EXPECT_EQ(stream.str(), "0000");
    }

    TEST(MoveTest, TestUCIEncodedRookMovePrint)
    {
        const Move move(Square::a1, Square::h1, Figure::WhiteRook, Figure::None, true, false, false, false);

        std::stringstream stream;

        stream << move;

        EXPECT_EQ(stream.str(), "a1h1");
    }
}