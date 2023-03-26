#pragma once

#include "MoveGenerations.h"

namespace ModernChess::AttackGeneration {

        namespace King
        {
            /**
             * @see https://www.chessprogramming.org/King_Pattern
             * @param kingSet
             * @return attack set
             */
            constexpr BitBoardState kingAttacks(BitBoardState kingSet)
            {
                BitBoardState attacks = MoveGenerations::oneStepEast(kingSet) | MoveGenerations::oneStepWest(kingSet);
                kingSet    |= attacks;
                attacks    |= MoveGenerations::oneStepNorth(kingSet) | MoveGenerations::oneStepSouth(kingSet);
                return attacks;
            }
        }

        constexpr std::array<BitBoardState, 64> generateKingAttacks()
        {
            // pawnAttackTable multipleAttacks table [square]
            std::array<BitBoardState, 64> attackTable{};

            // loop over 64 board squares
            for (Square square = Square::h8; square >= Square::a1; --square)
            {
                const BitBoardState state = BitBoardOperations::occupySquare(BoardState::empty, square);
                // init pawnAttackTable multipleAttacks
                attackTable[square] = King::kingAttacks(state);
            }

            return attackTable;
        }
    }