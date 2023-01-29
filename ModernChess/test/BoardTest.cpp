#include "ModernChess/Board.h"

#include <gtest/gtest.h>

namespace
{
    class ExtendedBoard : public ModernChess::Board
    {
    public:

        std::bitset<64> getBoardState()
        {
            return m_blackRookBitBoard & \
                   m_blackKnightBitBoard & \
                   m_blackBishopBitBoard & \
                   m_blackQueenBitBoard & \
                   m_blackKingBitBoard & \
                   m_blackPawnBitBoard & \
                   m_whiteRookBitBoard & \
                   m_whiteKnightBitBoard & \
                   m_whiteBishopBitBoard & \
                   m_whiteQueenBitBoard & \
                   m_whiteKingBitBoard & \
                   m_whitePawnBitBoard;
        }
    };

    TEST(Board, SquaresAreUniquelyOccupied)
    {
        ExtendedBoard board;

        EXPECT_EQ(board.getBoardState().to_ulong(), 0u);
    }
}


