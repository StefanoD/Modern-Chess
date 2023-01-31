#include "ModernChess/BitBoard.h"
#include "ModernChess/BitboardOperations.h"

#include <strstream>

namespace ModernChess
{

    BitBoard::BitBoard()
    {
        m_whiteRookBitBoard = BitboardOperations::occupySquare(m_whiteRookBitBoard, Square::a1);
        m_whiteRookBitBoard = BitboardOperations::occupySquare(m_whiteRookBitBoard, Square::h1);

        m_whiteKnightBitBoard = BitboardOperations::occupySquare(m_whiteKnightBitBoard, Square::b1);
        m_whiteKnightBitBoard = BitboardOperations::occupySquare(m_whiteKnightBitBoard, Square::g1);

        m_whiteBishopBitBoard = BitboardOperations::occupySquare(m_whiteBishopBitBoard, Square::c1);
        m_whiteBishopBitBoard = BitboardOperations::occupySquare(m_whiteBishopBitBoard, Square::f1);

        m_whiteQueenBitBoard = BitboardOperations::occupySquare(m_whiteQueenBitBoard, Square::d1);
        m_whiteKingBitBoard = BitboardOperations::occupySquare(m_whiteKingBitBoard, Square::e1);

        for (Square square = Square::a2; square <= Square::h2; ++square)
        {
            m_whitePawnBitBoard = BitboardOperations::occupySquare(m_whitePawnBitBoard, Square(square));
        }

        // Black figures have essentially the same position, just rotated by 180 degrees
        m_blackRookBitBoard = BitboardOperations::rotate180(m_whiteRookBitBoard);
        m_blackKnightBitBoard = BitboardOperations::rotate180(m_whiteKnightBitBoard);
        m_blackBishopBitBoard = BitboardOperations::rotate180(m_whiteBishopBitBoard);
        m_blackQueenBitBoard = BitboardOperations::rotate180(m_whiteQueenBitBoard);
        m_blackKingBitBoard = BitboardOperations::rotate180(m_whiteKingBitBoard);
        m_blackPawnBitBoard = BitboardOperations::rotate180(m_whitePawnBitBoard);
    }

    BitBoardState BitBoard::getOccupiedSquares() const
    {
        return m_blackRookBitBoard |
               m_blackKnightBitBoard |
               m_blackBishopBitBoard |
               m_blackQueenBitBoard |
               m_blackKingBitBoard |
               m_blackPawnBitBoard |
               m_whiteRookBitBoard |
               m_whiteKnightBitBoard |
               m_whiteBishopBitBoard |
               m_whiteQueenBitBoard |
               m_whiteKingBitBoard |
               m_whitePawnBitBoard;
    }

    BitBoardState BitBoard::getWhiteFigures() const
    {
        return m_whiteRookBitBoard |
               m_whiteKnightBitBoard |
               m_whiteBishopBitBoard |
               m_whiteQueenBitBoard |
               m_whiteKingBitBoard |
               m_whitePawnBitBoard;
    }

    BitBoardState BitBoard::getBlackFigures() const
    {
        return m_blackRookBitBoard |
               m_blackKnightBitBoard |
               m_blackBishopBitBoard |
               m_blackQueenBitBoard |
               m_blackKingBitBoard |
               m_blackPawnBitBoard;
    }

    BitBoardState BitBoard::getEmptySquares() const
    {
        return ~getOccupiedSquares();
    }

    std::string BitBoard::printBitBoard(const BitBoardState &bitBoard)
    {
        std::strstream stream;

        for (Square square = Square::h8; square >= Square::a1; --square)
        {
            stream << BitboardOperations::isOccupied(bitBoard, Square(square));

            if (square % 8 == 0)
            {
                stream << std::endl;
            }
        }

        return stream.str();
    }
}