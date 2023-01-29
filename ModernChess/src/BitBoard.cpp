#include "ModernChess/BitBoard.h"

#include <strstream>

namespace ModernChess
{

    BitBoard::BitBoard()
    {
        whiteRookBitBoard.set(0, true);
        whiteRookBitBoard.set(7, true);

        whiteKnightBitBoard.set(1, true);
        whiteKnightBitBoard.set(6, true);

        whiteBishopBitBoard.set(2, true);
        whiteBishopBitBoard.set(5, true);

        whiteQueenBitBoard.set(3, true);

        whiteKingBitBoard.set(4, true);

        for (int i = 8; i < 16; ++i)
        {
            whitePawnBitBoard.set(i, true);
        }

        blackRookBitBoard = std::rotr(whiteRookBitBoard.to_ulong(), 8);
        blackKnightBitBoard = std::rotr(whiteKnightBitBoard.to_ulong(), 8);
        blackBishopBitBoard = std::rotr(whiteBishopBitBoard.to_ulong(), 8);
        blackQueenBitBoard = std::rotr(whiteQueenBitBoard.to_ulong(), 8);
        blackKingBitBoard = std::rotr(whiteKingBitBoard.to_ulong(), 8);
        blackPawnBitBoard = std::rotr(whitePawnBitBoard.to_ulong(), 24);
    }

    BitBoardState BitBoard::getOccupiedSquares() const
    {
        return blackRookBitBoard | \
               blackKnightBitBoard | \
               blackBishopBitBoard | \
               blackQueenBitBoard | \
               blackKingBitBoard | \
               blackPawnBitBoard | \
               whiteRookBitBoard | \
               whiteKnightBitBoard | \
               whiteBishopBitBoard | \
               whiteQueenBitBoard | \
               whiteKingBitBoard | \
               whitePawnBitBoard;
    }

    BitBoardState BitBoard::getWhiteFigures() const
    {
        return whiteRookBitBoard | \
               whiteKnightBitBoard | \
               whiteBishopBitBoard | \
               whiteQueenBitBoard | \
               whiteKingBitBoard | \
               whitePawnBitBoard;
    }

    BitBoardState BitBoard::getBlackFigures() const
    {
        return blackRookBitBoard | \
               blackKnightBitBoard | \
               blackBishopBitBoard | \
               blackQueenBitBoard | \
               blackKingBitBoard | \
               blackPawnBitBoard;
    }

    BitBoardState BitBoard::getEmptySquares() const
    {
        return ~getOccupiedSquares();
    }

    std::string BitBoard::printBitBoard(const BitBoardState &bitBoard)
    {
        std::strstream stream;

        for (int square = numberSquares - 1; square >= 0; --square)
        {
            stream << bitBoard[square];

            if (square % 8 == 0)
            {
                stream << std::endl;
            }
        }

        return stream.str();
    }
}