#include "ModernChess/BitBoard.h"

#include <strstream>

namespace ModernChess
{

    BitBoard::BitBoard()
    {
        m_whiteRookBitBoard.set(0, true);
        m_whiteRookBitBoard.set(7, true);

        m_whiteKnightBitBoard.set(1, true);
        m_whiteKnightBitBoard.set(6, true);

        m_whiteBishopBitBoard.set(2, true);
        m_whiteBishopBitBoard.set(5, true);

        m_whiteQueenBitBoard.set(3, true);

        m_whiteKingBitBoard.set(4, true);

        for (int i = 8; i < 16; ++i)
        {
            m_whitePawnBitBoard.set(i, true);
        }

        m_blackRookBitBoard = std::rotr(m_whiteRookBitBoard.to_ulong(), 8);
        m_blackKnightBitBoard = std::rotr(m_whiteKnightBitBoard.to_ulong(), 8);
        m_blackBishopBitBoard = std::rotr(m_whiteBishopBitBoard.to_ulong(), 8);
        m_blackQueenBitBoard = std::rotr(m_whiteQueenBitBoard.to_ulong(), 8);
        m_blackKingBitBoard = std::rotr(m_whiteKingBitBoard.to_ulong(), 8);
        m_blackPawnBitBoard = std::rotr(m_whitePawnBitBoard.to_ulong(), 24);
    }

    BitBoardState BitBoard::getOccupiedSquares() const
    {
        return m_blackRookBitBoard | \
               m_blackKnightBitBoard | \
               m_blackBishopBitBoard | \
               m_blackQueenBitBoard | \
               m_blackKingBitBoard | \
               m_blackPawnBitBoard | \
               m_whiteRookBitBoard | \
               m_whiteKnightBitBoard | \
               m_whiteBishopBitBoard | \
               m_whiteQueenBitBoard | \
               m_whiteKingBitBoard | \
               m_whitePawnBitBoard;
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