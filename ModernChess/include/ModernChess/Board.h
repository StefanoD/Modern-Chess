#pragma once

#include <bitset>
#include <bit>

namespace ModernChess
{
    // TODO function to set starting state
    // TODO function to map from geometric to bitmap
    // TODO function to bitwise or all bitmaps -> board state
    // TODO function to bitwise and all bitmaps -> Piece captures (heterogeneous colors), illegal moves (homogenous colors) etc.
    // TODO function to map FEN notation to board state
    /**
     * @brief Every piece-type and every color has its own board representation
     */
    class Board
    {
    public:

        Board();

        std::bitset<64> getBitBoardState() const;

    protected:
        std::bitset<64> m_blackRookBitBoard;
        std::bitset<64> m_blackKnightBitBoard;
        std::bitset<64> m_blackBishopBitBoard;
        std::bitset<64> m_blackQueenBitBoard;
        std::bitset<64> m_blackKingBitBoard;
        std::bitset<64> m_blackPawnBitBoard;

        std::bitset<64> m_whiteRookBitBoard;
        std::bitset<64> m_whiteKnightBitBoard;
        std::bitset<64> m_whiteBishopBitBoard;
        std::bitset<64> m_whiteQueenBitBoard;
        std::bitset<64> m_whiteKingBitBoard;
        std::bitset<64> m_whitePawnBitBoard;
    };


}