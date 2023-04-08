#pragma once

#include "Square.h"

namespace ModernChess {

    enum SpecialMove : uint16_t {
        QuietMove = 0,
        DoublePawnPush = 1,
        KingCastle = 2,
        QueenCastle = 3,
        Capture = 4,
        EnPassantCapture = 5,
        KnightPromotion = 8,
        BishopPromotion = 9,
        RookPromotion = 10,
        QueenPromotion = 11,
        KnightPromotionCapture = 12,
        BishopPromotionCapture = 13,
        RookPromotionCapture = 14,
        QueenPromotionCapture = 15,
    };

    /**
     * @see https://www.chessprogramming.org/Encoding_Moves
     */
    struct Move
    {
        explicit Move(Square from, Square to, SpecialMove specialMove) :
                m_move{((specialMove & 0xF) << 12) | ((from & 0x3F) << 6) | (to & 0x3F)}
            {}

        [[nodiscard]] Square getTo() const
        {
            return Square(m_move & 0x3F);
        }

        [[nodiscard]] Square getFrom() const
        {
            return Square((m_move >> 6) & 0x3F);
        }
        
        [[nodiscard]] SpecialMove getSpecialMove() const
        {
            return SpecialMove((m_move >> 12) & 0x0F);
        }

        [[nodiscard]] bool isCapture() const
        {
            return (m_move & SpecialMove::Capture) != 0;
        }

        [[nodiscard]] int32_t getButterflyIndex() const
        {
            return m_move & 0x0FFF;
        }

        void setTo(Square to)
        {
            m_move &= ~0x3F; 
            m_move |= to & 0x3F;
        }
        
        void setFrom(Square from)
        {
            m_move &= ~0xFC0;
            m_move |= (from & 0x3F) << 6;
        }

    private:
        int32_t m_move;
    };

}