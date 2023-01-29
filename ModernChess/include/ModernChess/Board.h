#pragma once

#include <bitset>
#include <bit>
#include <string>

namespace ModernChess
{

    using BitBoard = std::bitset<64>;

    // TODO Square-centric representation \
    //  - function to map FEN notation to board state
    //  - function to map from geometric to bitmap

    // TODO function to bitwise and all bitmaps -> Piece captures (different colors), illegal moves (same colors) etc.
    class Board
    {
    public:

        Board();

        [[nodiscard]] BitBoard getOccupiedSquares() const;
        [[nodiscard]] std::string toString() const;

    protected:
        // Every piece-type and every color has its own board representation
        BitBoard m_blackRookBitBoard;
        BitBoard m_blackKnightBitBoard;
        BitBoard m_blackBishopBitBoard;
        BitBoard m_blackQueenBitBoard;
        BitBoard m_blackKingBitBoard;
        BitBoard m_blackPawnBitBoard;

        BitBoard m_whiteRookBitBoard;
        BitBoard m_whiteKnightBitBoard;
        BitBoard m_whiteBishopBitBoard;
        BitBoard m_whiteQueenBitBoard;
        BitBoard m_whiteKingBitBoard;
        BitBoard m_whitePawnBitBoard;
    };


}