#include "ModernChess/SlidingPieceAttackGeneration.h"

namespace ModernChess::AttackGeneration::SlidingPieces {

    BishopAttacks::BishopAttacks()
    {
        // loop over 64 board squares
        for (int squareIndex = 0; squareIndex < 64; ++squareIndex)
        {
            const Square square{squareIndex};

            // init figure & bishop masks
            bishopAttackMasks[square] = maskBishopAttacks(square);

            // init current mask
            const uint64_t attackMask = bishopAttackMasks[square];

            // init relevant occupancy bit count
            const uint32_t relevantBitsCount = BitBoardOperations::countBits(attackMask);

            // init occupancy indices
            const uint32_t occupancyIndices = (1 << relevantBitsCount);

            // loop over occupancy indices
            for (uint32_t index = 0; index < occupancyIndices; ++index)
            {
                // init current occupancy variation
                const uint64_t occupancy = setOccupancy(index, relevantBitsCount, attackMask);

                // init magic index
                const uint32_t magicIndex = (occupancy * BishopMetaData::magicNumbers[square]) >> (64 - BishopMetaData::relevantBits[square]);

                // init figure attacks
                bishopAttacks[square][magicIndex] = bishopAttacksOnTheFly(occupancy, square);
            }
        }
    }

    RookAttacks::RookAttacks()
    {
        // init slider piece's attack tables
        // loop over 64 board squares
        for (int squareIndex = 0; squareIndex < 64; ++squareIndex)
        {
            const Square square{squareIndex};

            // init figure & rook masks
            rookAttackMasks[square] = maskRookAttacks(square);

            // init current mask
            const uint64_t attackMask = rookAttackMasks[square];

            // init relevant occupancy bit count
            const uint32_t relevantBitsCount = BitBoardOperations::countBits(attackMask);

            // init occupancy indices
            const uint32_t occupancyIndices = (1 << relevantBitsCount);

            // loop over occupancy indices
            for (uint32_t index = 0; index < occupancyIndices; ++index)
            {
                // init current occupancy variation
                const uint64_t occupancy = setOccupancy(index, relevantBitsCount, attackMask);

                // init magic index
                const uint32_t magicIndex = (occupancy * RookMetaData::magicNumbers[square]) >> (64 - RookMetaData::relevantBits[square]);

                // init figure attacks
                rookAttacks[square][magicIndex] = rookAttacksOnTheFly(occupancy, square);
            }
        }
    }
}