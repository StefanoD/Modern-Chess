#include "ModernChess/SlidingPieceAttackGeneration.h"

namespace ModernChess::AttackGeneration::SlidingPieces {

    BishopAttacks::BishopAttacks()
    {
        // loop over 64 board squares
        for (int squareIndex = 0; squareIndex < 64; ++squareIndex)
        {
            const Square square{squareIndex};

            // init figure & bishop masks
            bishopMasks.at(square) = maskBishopAttacks(square);

            // init current mask
            const uint64_t attackMask = bishopMasks.at(square);

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
                const uint32_t magicIndex = (occupancy * BishopMetaData::bishopMagicNumbers.at(square)) >> (64 - BishopMetaData::bishopRelevantBits.at(square));

                // init figure attacks
                bishopAttacks.at(square).at(magicIndex) = bishopAttacksOnTheFly(occupancy, square);
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
            rookMasks.at(square) = maskRookAttacks(square);

            // init current mask
            const uint64_t attackMask = rookMasks.at(square);

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
                const uint32_t magicIndex = (occupancy * RookMetaData::rookMagicNumbers.at(square)) >> (64 - RookMetaData::rookRelevantBits.at(square));

                // init figure attacks
                rookAttacks.at(square).at(magicIndex) = rookAttacksOnTheFly(occupancy, square);
            }
        }
    }
}