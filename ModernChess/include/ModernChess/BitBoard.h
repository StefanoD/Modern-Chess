#pragma once

#include "BitBoardConstants.h"

namespace ModernChess
{


    // TODO Square-centric representation \
    //  - function to map FEN notation to board state
    //  - function to map from geometric to bitmap

    // TODO function to bitwise and all bitmaps -> Piece captures (different colors), illegal moves (same colors) etc.
    class BitBoard
    {
    public:

        BitBoard();

        [[nodiscard]] BitBoardState getOccupiedSquares() const;
        [[nodiscard]] BitBoardState getEmptySquares() const;
        [[nodiscard]] BitBoardState getWhiteFigures() const;
        [[nodiscard]] BitBoardState getBlackFigures() const;

    protected:
        // Every piece-type and every color has its own board representation
        BitBoardState m_blackRookBitBoard{};
        BitBoardState m_blackKnightBitBoard{};
        BitBoardState m_blackBishopBitBoard{};
        BitBoardState m_blackQueenBitBoard{};
        BitBoardState m_blackKingBitBoard{};
        BitBoardState m_blackPawnBitBoard{};

        BitBoardState m_whiteRookBitBoard{};
        BitBoardState m_whiteKnightBitBoard{};
        BitBoardState m_whiteBishopBitBoard{};
        BitBoardState m_whiteQueenBitBoard{};
        BitBoardState m_whiteKingBitBoard{};
        BitBoardState m_whitePawnBitBoard{};
    };
}