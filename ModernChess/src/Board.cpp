#include "ModernChess/Board.h"

#include <strstream>

namespace ModernChess
{

    Board::Board()
    {
        m_blackRookBitBoard.set(0, true);
        m_blackRookBitBoard.set(7, true);

        m_blackKnightBitBoard.set(1, true);
        m_blackKnightBitBoard.set(6, true);

        m_blackBishopBitBoard.set(2, true);
        m_blackBishopBitBoard.set(5, true);

        m_blackQueenBitBoard.set(3, true);

        m_blackKingBitBoard.set(4, true);

        for (int i = 8; i < 16; ++i)
        {
            m_blackPawnBitBoard.set(i, true);
        }

        m_whiteRookBitBoard = std::rotr(m_blackRookBitBoard.to_ulong(), 8);
        m_whiteKnightBitBoard = std::rotr(m_blackKnightBitBoard.to_ulong(), 8);
        m_whiteBishopBitBoard = std::rotr(m_blackBishopBitBoard.to_ulong(), 8);
        m_whiteQueenBitBoard = std::rotr(m_blackQueenBitBoard.to_ulong(), 8);
        m_whiteKingBitBoard = std::rotr(m_blackKingBitBoard.to_ulong(), 8);
        m_whitePawnBitBoard = std::rotr(m_blackPawnBitBoard.to_ulong(), 24);
    }

    BitBoard Board::getBitBoardState() const
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

    std::string Board::toString() const
    {
        const BitBoard bitBoardState = getBitBoardState();
        std::strstream stream;

        for (uint8_t square = 0; square < 64; ++square)
        {
            if (square % 8 == 0)
            {
                stream << std::endl;
            }

            stream << bitBoardState[square];
        }

        return stream.str();
    }
}