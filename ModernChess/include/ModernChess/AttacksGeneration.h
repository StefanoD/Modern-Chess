#pragma once

#include "BitBoardConstants.h"
#include "MoveGenerations.h"
#include "Square.h"

namespace ModernChess
{
    // Attack calculations on an empty board which is here named "empty squares".
    // See https://www.chessemptyBoardgramming.org/On_an_empty_Board and
    // https://www.chessemptyBoardgramming.org/Kogge-Stone_Algorithm

    namespace Ray {

        /**
         * @brief Attacking ray towards north until it hits a figure
         * @param pieceBoard Board which has the attacking pieces of one kind
         * @param emptySquares An inverted play board where empty square bits are set to 1.
         * @return All attacking squares until the ray hits a figure
         */
        constexpr BitBoardState northOccluded(BitBoardState pieceBoard, BitBoardState emptySquares)
        {
            pieceBoard |= emptySquares & (pieceBoard << 8);
            emptySquares &= (emptySquares << 8);
            pieceBoard |= emptySquares & (pieceBoard << 16);
            emptySquares &= (emptySquares << 16);
            pieceBoard |= emptySquares & (pieceBoard << 32);
            return pieceBoard;
        }

        constexpr BitBoardState southOccluded(BitBoardState pieceBoard, BitBoardState emptySquares)
        {
            pieceBoard |= emptySquares & (pieceBoard >> 8);
            emptySquares &= (emptySquares >> 8);
            pieceBoard |= emptySquares & (pieceBoard >> 16);
            emptySquares &= (emptySquares >> 16);
            pieceBoard |= emptySquares & (pieceBoard >> 32);
            return pieceBoard;
        }

        constexpr BitBoardState eastOccluded(BitBoardState pieceBoard, BitBoardState emptySquares)
        {
            emptySquares &= BitBoardConstants::notAFile;
            pieceBoard |= emptySquares & (pieceBoard << 1);
            emptySquares &= (emptySquares << 1);
            pieceBoard |= emptySquares & (pieceBoard << 2);
            emptySquares &= (emptySquares << 2);
            pieceBoard |= emptySquares & (pieceBoard << 4);
            return pieceBoard;
        }

        constexpr BitBoardState northEastOccluded(BitBoardState pieceBoard, BitBoardState emptySquares)
        {
            emptySquares &= BitBoardConstants::notAFile;
            pieceBoard |= emptySquares & (pieceBoard << 9);
            emptySquares &= (emptySquares << 9);
            pieceBoard |= emptySquares & (pieceBoard << 18);
            emptySquares &= (emptySquares << 18);
            pieceBoard |= emptySquares & (pieceBoard << 36);
            return pieceBoard;
        }

        constexpr BitBoardState southEastOccluded(BitBoardState pieceBoard, BitBoardState emptySquares)
        {
            emptySquares &= BitBoardConstants::notAFile;
            pieceBoard |= emptySquares & (pieceBoard >> 7);
            emptySquares &= (emptySquares >> 7);
            pieceBoard |= emptySquares & (pieceBoard >> 14);
            emptySquares &= (emptySquares >> 14);
            pieceBoard |= emptySquares & (pieceBoard >> 28);
            return pieceBoard;
        }

        constexpr BitBoardState westOccluded(BitBoardState pieceBoard, BitBoardState emptySquares)
        {
            emptySquares &= BitBoardConstants::notHFile;
            pieceBoard |= emptySquares & (pieceBoard >> 1);
            emptySquares &= (emptySquares >> 1);
            pieceBoard |= emptySquares & (pieceBoard >> 2);
            emptySquares &= (emptySquares >> 2);
            pieceBoard |= emptySquares & (pieceBoard >> 4);
            return pieceBoard;
        }

        constexpr BitBoardState southWestOccluded(BitBoardState pieceBoard, BitBoardState emptySquares)
        {
            emptySquares &= BitBoardConstants::notHFile;
            pieceBoard |= emptySquares & (pieceBoard >> 9);
            emptySquares &= (emptySquares >> 9);
            pieceBoard |= emptySquares & (pieceBoard >> 18);
            emptySquares &= (emptySquares >> 18);
            pieceBoard |= emptySquares & (pieceBoard >> 36);
            return pieceBoard;
        }

        constexpr BitBoardState northWestOccluded(BitBoardState pieceBoard, BitBoardState emptySquares)
        {
            emptySquares &= BitBoardConstants::notHFile;
            pieceBoard |= emptySquares & (pieceBoard << 7);
            emptySquares &= (emptySquares << 7);
            pieceBoard |= emptySquares & (pieceBoard << 14);
            emptySquares &= (emptySquares << 14);
            pieceBoard |= emptySquares & (pieceBoard << 28);
            return pieceBoard;
        }
    }

    namespace RookAttack {
        /**
         * @brief A north ray attack from rooks
         * @param rooks board with rooks
         * @param emptySquares An inverted play board where empty square bits are set to 1.
         * @return All attacking squares
         */
        constexpr BitBoardState north(BitBoardState rooks, BitBoardState emptySquares)
        {
            return MoveGenerations::oneStepNorth(Ray::northOccluded(rooks, emptySquares));
        }

        constexpr BitBoardState south(BitBoardState rooks, BitBoardState emptySquares)
        {
            return MoveGenerations::oneStepSouth(Ray::southOccluded(rooks, emptySquares));
        }

        constexpr BitBoardState east(BitBoardState rooks, BitBoardState emptySquares)
        {
            return MoveGenerations::oneStepEast(Ray::eastOccluded(rooks, emptySquares));
        }

        constexpr BitBoardState west(BitBoardState rooks, BitBoardState emptySquares)
        {
            return MoveGenerations::oneStepWest(Ray::westOccluded(rooks, emptySquares));
        }
    }

    namespace BishopAttack
    {
        /**
         * @brief A north-east ray attack from bishops
         * @param bishops board with bishops
         * @param emptySquares An inverted play board where empty square bits are set to 1.
         * @return All attacking squares
         */
        constexpr BitBoardState northEast(BitBoardState bishops, BitBoardState emptySquares)
        {
            return MoveGenerations::oneStepNorthEast(Ray::northEastOccluded(bishops, emptySquares));
        }

        constexpr BitBoardState southEast(BitBoardState bishops, BitBoardState emptySquares)
        {
            return MoveGenerations::oneStepSouthEast(Ray::southEastOccluded(bishops, emptySquares));
        }

        constexpr BitBoardState southWest(BitBoardState bishops, BitBoardState emptySquares)
        {
            return MoveGenerations::oneStepSouthWest(Ray::southWestOccluded(bishops, emptySquares));
        }

        constexpr BitBoardState northWest(BitBoardState bishops, BitBoardState emptySquares)
        {
            return MoveGenerations::oneStepNorthWest(Ray::northWestOccluded(bishops, emptySquares));
        }
    }

    namespace WhitePawnsAttacks
    {
        // See https://www.chessprogramming.org/Pawn_Attacks_(Bitboards)

        constexpr BitBoardState east(BitBoardState whitePawns)
        {
            return MoveGenerations::oneStepNorthEast(whitePawns);
        }

        constexpr BitBoardState west(BitBoardState whitePawns)
        {
            return MoveGenerations::oneStepNorthWest(whitePawns);
        }
    }

    namespace BlackPawnsAttacks
    {
        // See https://www.chessprogramming.org/Pawn_Attacks_(Bitboards)

        constexpr BitBoardState east(BitBoardState blackPawns)
        {
            return MoveGenerations::oneStepSouthEast(blackPawns);
        }

        constexpr BitBoardState west(BitBoardState blackPawns)
        {
            return MoveGenerations::oneStepSouthWest(blackPawns);
        }
    }

    constexpr BitBoardState northFill(BitBoardState gen)
    {
        gen |= (gen << 8);
        gen |= (gen << 16);
        gen |= (gen << 32);
        return gen;
    }

    constexpr BitBoardState rankMask(Square square)
    {
        return  BitBoardConstants::rank1 << (square & 56);
    }

    constexpr BitBoardState fileMask(Square square)
    {
        return BitBoardConstants::aFile << (square & 7);
    }

    constexpr BitBoardState diagonalMask(Square square)
    {
        const int diagonal = 8 * (square & 7) - (square & 56);
        const int north = -diagonal & (diagonal >> 31);
        const int south = diagonal & (-diagonal >> 31);
        return (BitBoardConstants::a1H8Diagonal >> south) << north;
    }
}