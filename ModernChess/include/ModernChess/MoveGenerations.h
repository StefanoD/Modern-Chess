#pragma once

#include "BitBoardOperations.h"

namespace ModernChess::MoveGenerations
{
    static constexpr BitBoardState oneStepNorth(BitBoardState state)
    {
        return state << 8;
    }

    static constexpr BitBoardState oneStepSouth(BitBoardState state)
    {
        return state >> 8;
    }

    static constexpr BitBoardState oneStepEast(BitBoardState state)
    {
        return (state << 1) & BitBoardConstants::notAFile;
    }

    static constexpr BitBoardState oneStepNorthEast(BitBoardState state)
    {
        return (state << 9) & BitBoardConstants::notAFile;
    }

    static constexpr BitBoardState oneStepSouthEast(BitBoardState state)
    {
        return (state >> 7) & BitBoardConstants::notAFile;
    }

    static constexpr BitBoardState oneStepWest(BitBoardState state)
    {
        return (state >> 1) & BitBoardConstants::notHFile;
    }

    static constexpr BitBoardState oneStepSouthWest(BitBoardState state)
    {
        return (state >> 9) & BitBoardConstants::notHFile;
    }

    static constexpr BitBoardState oneStepNorthWest(BitBoardState state)
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
        static constexpr BitBoardState singlePush(BitBoardState whitePawns, BitBoardState emptySquares)
        {
            return oneStepNorth(whitePawns) & emptySquares;
        }

        /**
         * @param whitePawns board with white pawns
         * @param emptySquares An inverted play board where empty square bits are set to 1.
         * @return Resulting board where all white pawns have been pushed by two square
         */
        static constexpr BitBoardState doublePush(BitBoardState whitePawns, BitBoardState emptySquares)
        {
            const BitBoardState singlePushs = singlePush(whitePawns, emptySquares);
            return oneStepNorth(singlePushs) & emptySquares & BitBoardConstants::rank4;
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
        static constexpr BitBoardState singlePush(BitBoardState blackPawns, BitBoardState emptySquares)
        {
            return oneStepSouth(blackPawns) & emptySquares;
        }

        /**
         * @param blackPawns board with black pawns
         * @param emptySquares An inverted play board where empty square bits are set to 1.
         * @return Resulting board where all black pawns have been pushed by two square
         */
        static constexpr BitBoardState doublePush(BitBoardState blackPawns, BitBoardState emptySquares)
        {
            const BitBoardState singlePushs = singlePush(blackPawns, emptySquares);
            return oneStepSouth(singlePushs) & emptySquares & BitBoardConstants::rank5;
        }
    }
}