#pragma once

#include "BitBoardOperations.h"

namespace ModernChess::MoveGenerations
{
    constexpr BitBoardState oneStepNorth(BitBoardState state)
    {
        return state << 8;
    }

    constexpr BitBoardState oneStepSouth(BitBoardState state)
    {
        return state >> 8;
    }

    constexpr BitBoardState oneStepEast(BitBoardState state)
    {
        return (state << 1) & BitBoardConstants::notAFile;
    }

    constexpr BitBoardState oneStepNorthEast(BitBoardState state)
    {
        return (state << 9) & BitBoardConstants::notAFile;
    }

    constexpr BitBoardState oneStepSouthEast(BitBoardState state)
    {
        return (state >> 7) & BitBoardConstants::notAFile;
    }

    constexpr BitBoardState oneStepWest(BitBoardState state)
    {
        return (state >> 1) & BitBoardConstants::notHFile;
    }

    constexpr BitBoardState oneStepSouthWest(BitBoardState state)
    {
        return (state >> 9) & BitBoardConstants::notHFile;
    }

    constexpr BitBoardState oneStepNorthWest(BitBoardState state)
    {
        return (state << 7) & BitBoardConstants::notHFile;
    }

    namespace WhitePawns
    {
        // See https://www.chessprogramming.org/Pawn_Pushes_(Bitboards)#GeneralizedPush

        /**
         * @param whitePawns board with white pawns
         * @param emptySquares An inverted play board where empty square bits are set to 1.
         * @return Resulting board where all white pawns have been pushed by one square
         */
        constexpr BitBoardState singlePush(BitBoardState whitePawns, BitBoardState emptySquares)
        {
            return oneStepNorth(whitePawns) & emptySquares;
        }

        /**
         * @param whitePawns board with white pawns
         * @param emptySquares An inverted play board where empty square bits are set to 1.
         * @return Resulting board where all white pawns have been pushed by two square
         */
        constexpr BitBoardState doublePush(BitBoardState whitePawns, BitBoardState emptySquares)
        {
            const BitBoardState singlePushs = singlePush(whitePawns, emptySquares);
            return oneStepNorth(singlePushs) & emptySquares & BitBoardConstants::rank4;
        }

        static constexpr bool singlePushPossible(BitBoardState whitePawns, BitBoardState emptySquares)
        {
            // To get the set of source squares of pawns able to push is about intersection of pawns with the shifted
            // empty squares in opposite direction:
            return oneStepSouth(emptySquares) & whitePawns;
        }

        static constexpr bool doublePushPossible(BitBoardState whitePawns, BitBoardState emptySquares)
        {
            const BitBoardState emptyRank3 = oneStepSouth(emptySquares & BitBoardConstants::rank4) & emptySquares;
            return singlePushPossible(whitePawns, emptyRank3);
        }
    }

    namespace BlackPawns
    {
        // See https://www.chessprogramming.org/Pawn_Pushes_(Bitboards)#GeneralizedPush

        /**
         * @param blackPawns board with black pawns
         * @param emptySquares An inverted play board where empty square bits are set to 1.
         * @return Resulting board where all black pawns have been pushed by one square
         */
        constexpr BitBoardState singlePush(BitBoardState blackPawns, BitBoardState emptySquares)
        {
            return oneStepSouth(blackPawns) & emptySquares;
        }

        /**
         * @param blackPawns board with black pawns
         * @param emptySquares An inverted play board where empty square bits are set to 1.
         * @return Resulting board where all black pawns have been pushed by two square
         */
        constexpr BitBoardState doublePush(BitBoardState blackPawns, BitBoardState emptySquares)
        {
            const BitBoardState singlePushs = singlePush(blackPawns, emptySquares);
            return oneStepSouth(singlePushs) & emptySquares & BitBoardConstants::rank5;
        }

        static constexpr bool singlePushPossible(BitBoardState blackPawns, BitBoardState emptySquares)
        {
            // To get the set of source squares of pawns able to push is about intersection of pawns with the shifted
            // empty squares in opposite direction:
            return oneStepNorth(emptySquares) & blackPawns;
        }

        static constexpr bool doublePushPossible(BitBoardState blackPawns, BitBoardState emptySquares)
        {
            const BitBoardState emptyRank6 = oneStepNorth(emptySquares & BitBoardConstants::rank5) & emptySquares;
            return singlePushPossible(blackPawns, emptyRank6);
        }
    }
}