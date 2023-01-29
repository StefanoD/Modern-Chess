#pragma once

#include <bitset>
#include <bit>
#include <string>

namespace ModernChess
{
    // TODO function to map from geometric to bitmap
    // TODO function to bitwise and all bitmaps -> Piece captures (different colors), illegal moves (same colors) etc.
    // TODO function to map FEN notation to board state
    /**
     * @brief Every piece-type and every color has its own board representation
     */
    class Board
    {
    public:

        Board();

        [[nodiscard]] std::bitset<64> getBitBoardState() const;
        [[nodiscard]] std::string toString() const;

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