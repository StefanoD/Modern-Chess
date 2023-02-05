#pragma once

#include "BitBoardConstants.h"
#include "BitBoardOperations.h"
#include "Square.h"

namespace ModernChess
{
    // Attack calculations on an empty board.
    // See https://www.chessemptyBoardgramming.org/On_an_empty_Board and
    // https://www.chessemptyBoardgramming.org/Kogge-Stone_Algorithm

    namespace Ray {

        constexpr BitBoardState northOccluded(BitBoardState pieceBoard, BitBoardState emptyBoard)
        {
            pieceBoard |= emptyBoard & (pieceBoard << 8);
            emptyBoard &= (emptyBoard << 8);
            pieceBoard |= emptyBoard & (pieceBoard << 16);
            emptyBoard &= (emptyBoard << 16);
            pieceBoard |= emptyBoard & (pieceBoard << 32);
            return pieceBoard;
        }

        constexpr BitBoardState southOccluded(BitBoardState pieceBoard, BitBoardState emptyBoard)
        {
            pieceBoard |= emptyBoard & (pieceBoard >>  8);
            emptyBoard &= (emptyBoard >>  8);
            pieceBoard |= emptyBoard & (pieceBoard >> 16);
            emptyBoard &= (emptyBoard >> 16);
            pieceBoard |= emptyBoard & (pieceBoard >> 32);
            return pieceBoard;
        }

        constexpr BitBoardState eastOccluded(BitBoardState pieceBoard, BitBoardState emptyBoard)
        {
            emptyBoard &= BitBoardConstants::notAFile;
            pieceBoard |= emptyBoard & (pieceBoard << 1);
            emptyBoard &= (emptyBoard << 1);
            pieceBoard |= emptyBoard & (pieceBoard << 2);
            emptyBoard &= (emptyBoard << 2);
            pieceBoard |= emptyBoard & (pieceBoard << 4);
            return pieceBoard;
        }

        constexpr BitBoardState northEastOccluded(BitBoardState pieceBoard, BitBoardState emptyBoard)
        {
            emptyBoard &= BitBoardConstants::notAFile;
            pieceBoard |= emptyBoard & (pieceBoard <<  9);
            emptyBoard &= (emptyBoard <<  9);
            pieceBoard |= emptyBoard & (pieceBoard << 18);
            emptyBoard &= (emptyBoard << 18);
            pieceBoard |= emptyBoard & (pieceBoard << 36);
            return pieceBoard;
        }

        constexpr BitBoardState southEastOccluded(BitBoardState pieceBoard, BitBoardState emptyBoard)
        {
            emptyBoard &= BitBoardConstants::notAFile;
            pieceBoard |= emptyBoard & (pieceBoard >>  7);
            emptyBoard &= (emptyBoard >>  7);
            pieceBoard |= emptyBoard & (pieceBoard >> 14);
            emptyBoard &= (emptyBoard >> 14);
            pieceBoard |= emptyBoard & (pieceBoard >> 28);
            return pieceBoard;
        }

        constexpr BitBoardState westOccluded(BitBoardState pieceBoard, BitBoardState emptyBoard)
        {
            emptyBoard &= BitBoardConstants::notHFile;
            pieceBoard |= emptyBoard & (pieceBoard >> 1);
            emptyBoard &= (emptyBoard >> 1);
            pieceBoard |= emptyBoard & (pieceBoard >> 2);
            emptyBoard &= (emptyBoard >> 2);
            pieceBoard |= emptyBoard & (pieceBoard >> 4);
            return pieceBoard;
        }

        constexpr BitBoardState southWestOccluded(BitBoardState pieceBoard, BitBoardState emptyBoard)
        {
            emptyBoard &= BitBoardConstants::notHFile;
            pieceBoard |= emptyBoard & (pieceBoard >>  9);
            emptyBoard &= (emptyBoard >>  9);
            pieceBoard |= emptyBoard & (pieceBoard >> 18);
            emptyBoard &= (emptyBoard >> 18);
            pieceBoard |= emptyBoard & (pieceBoard >> 36);
            return pieceBoard;
        }

        constexpr BitBoardState northWestOccluded(BitBoardState pieceBoard, BitBoardState emptyBoard)
        {
            emptyBoard &= BitBoardConstants::notHFile;
            pieceBoard |= emptyBoard & (pieceBoard <<  7);
            emptyBoard &= (emptyBoard <<  7);
            pieceBoard |= emptyBoard & (pieceBoard << 14);
            emptyBoard &= (emptyBoard << 14);
            pieceBoard |= emptyBoard & (pieceBoard << 28);
            return pieceBoard;
        }
    }

    namespace RookAttack {
        /**
         * @brief A north ray attack from rooks
         * @param rooks board with rooks
         * @param emptySquares Board where empty squares bits are set to 1.
         * @return All attacking squares
         */
        constexpr BitBoardState north(BitBoardState rooks, BitBoardState emptySquares)
        {
            return BitBoardOperations::oneStepNorth(Ray::northOccluded(rooks, emptySquares));
        }

        BitBoardState south(BitBoardState rooks, BitBoardState emptySquares)
        {
            return BitBoardOperations::oneStepSouth(Ray::southOccluded(rooks, emptySquares));
        }

        BitBoardState east(BitBoardState rooks, BitBoardState emptySquares)
        {
            return BitBoardOperations::oneStepEast(Ray::eastOccluded(rooks, emptySquares));
        }

        BitBoardState west(BitBoardState rooks, BitBoardState emptySquares)
        {
            return BitBoardOperations::oneStepWest(Ray::westOccluded(rooks, emptySquares));
        }
    }

    namespace BishopAttack
    {
        BitBoardState northEast(BitBoardState bishops, BitBoardState emptySquares)
        {
            return BitBoardOperations::oneStepNorthEast(Ray::northEastOccluded(bishops, emptySquares));
        }

        BitBoardState southEast(BitBoardState bishops, BitBoardState emptySquares)
        {
            return BitBoardOperations::oneStepSouthEast(Ray::southEastOccluded(bishops, emptySquares));
        }

        BitBoardState southWest(BitBoardState bishops, BitBoardState emptySquares)
        {
            return BitBoardOperations::oneStepSouthWest(Ray::southWestOccluded(bishops, emptySquares));
        }

        BitBoardState northWest(BitBoardState bishops, BitBoardState emptySquares)
        {
            return BitBoardOperations::oneStepNorthWest(Ray::northWestOccluded(bishops, emptySquares));
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
        return  BitBoardConstants::firstRank << (square & 56);
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