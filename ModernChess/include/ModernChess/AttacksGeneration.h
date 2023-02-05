#pragma once

#include "BitBoardConstants.h"
#include "BitBoardOperations.h"
#include "Square.h"

namespace ModernChess::AttacksGeneration
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
            emptyBoard &=       (emptyBoard >>  8);
            pieceBoard |= emptyBoard & (pieceBoard >> 16);
            emptyBoard &=       (emptyBoard >> 16);
            pieceBoard |= emptyBoard & (pieceBoard >> 32);
            return pieceBoard;
        }

        constexpr BitBoardState eastOccluded(BitBoardState pieceBoard, BitBoardState emptyBoard)
        {
            emptyBoard &= BitBoardConstants::notAFile;
            pieceBoard |= emptyBoard & (pieceBoard << 1);
            emptyBoard &=       (emptyBoard << 1);
            pieceBoard |= emptyBoard & (pieceBoard << 2);
            emptyBoard &=       (emptyBoard << 2);
            pieceBoard |= emptyBoard & (pieceBoard << 4);
            return pieceBoard;
        }

        constexpr BitBoardState northEastOccluded(BitBoardState pieceBoard, BitBoardState emptyBoard)
        {
            emptyBoard &= BitBoardConstants::notAFile;
            pieceBoard |= emptyBoard & (pieceBoard <<  9);
            emptyBoard &=       (emptyBoard <<  9);
            pieceBoard |= emptyBoard & (pieceBoard << 18);
            emptyBoard &=       (emptyBoard << 18);
            pieceBoard |= emptyBoard & (pieceBoard << 36);
            return pieceBoard;
        }

        constexpr BitBoardState southEastOccluded(BitBoardState pieceBoard, BitBoardState emptyBoard)
        {
            emptyBoard &= BitBoardConstants::notAFile;
            pieceBoard |= emptyBoard & (pieceBoard >>  7);
            emptyBoard &=       (emptyBoard >>  7);
            pieceBoard |= emptyBoard & (pieceBoard >> 14);
            emptyBoard &=       (emptyBoard >> 14);
            pieceBoard |= emptyBoard & (pieceBoard >> 28);
            return pieceBoard;
        }

        constexpr BitBoardState westOccluded(BitBoardState pieceBoard, BitBoardState emptyBoard)
        {
            emptyBoard &= BitBoardConstants::notHFile;
            pieceBoard |= emptyBoard & (pieceBoard >> 1);
            emptyBoard &=       (emptyBoard >> 1);
            pieceBoard |= emptyBoard & (pieceBoard >> 2);
            emptyBoard &=       (emptyBoard >> 2);
            pieceBoard |= emptyBoard & (pieceBoard >> 4);
            return pieceBoard;
        }

        constexpr BitBoardState southWestOccluded(BitBoardState pieceBoard, BitBoardState emptyBoard)
        {
            emptyBoard &= BitBoardConstants::notHFile;
            pieceBoard |= emptyBoard & (pieceBoard >>  9);
            emptyBoard &=       (emptyBoard >>  9);
            pieceBoard |= emptyBoard & (pieceBoard >> 18);
            emptyBoard &=       (emptyBoard >> 18);
            pieceBoard |= emptyBoard & (pieceBoard >> 36);
            return pieceBoard;
        }

        constexpr BitBoardState northWestOccluded(BitBoardState pieceBoard, BitBoardState emptyBoard)
        {
            emptyBoard &= BitBoardConstants::notHFile;
            pieceBoard |= emptyBoard & (pieceBoard <<  7);
            emptyBoard &=       (emptyBoard <<  7);
            pieceBoard |= emptyBoard & (pieceBoard << 14);
            emptyBoard &=       (emptyBoard << 14);
            pieceBoard |= emptyBoard & (pieceBoard << 28);
            return pieceBoard;
        }
    }


    /**
     * @brief A north ray attack from rooks
     * @param rooks board with rooks
     * @param emptyBoard Board where empty squares bit are set to 1.
     * @return All attacking squares
     */
    constexpr BitBoardState northAttacks(BitBoardState rooks, BitBoardState emptyBoard)
    {
        return BitBoardOperations::oneStepNorth(Ray::northOccluded(rooks, emptyBoard));
    }
    
    BitBoardState southAttacks (BitBoardState rooks,   BitBoardState empty)
    {
        return BitBoardOperations::oneStepSouth(Ray::southOccluded(rooks, empty));
    }

    BitBoardState eastAttacks (BitBoardState rooks,   BitBoardState empty)
    {
        return BitBoardOperations::oneStepEast(Ray::eastOccluded(rooks, empty));
    }

    BitBoardState northEastAttacks (BitBoardState bishops, BitBoardState empty)
    {
        return BitBoardOperations::oneStepNorthEast(Ray::northEastOccluded(bishops, empty));
    }

    BitBoardState southEastAttacks (BitBoardState bishops, BitBoardState empty)
    {
        return BitBoardOperations::oneStepSouthEast(Ray::southEastOccluded(bishops, empty));
    }

    BitBoardState westAttacks (BitBoardState rooks,   BitBoardState empty)
    {
        return BitBoardOperations::oneStepWest(Ray::westOccluded(rooks, empty));
    }

    BitBoardState soutWestAttacks (BitBoardState bishops, BitBoardState empty)
    {
        return BitBoardOperations::oneStepSouthWest(Ray::southWestOccluded(bishops, empty));
    }

    BitBoardState northWestAttacks (BitBoardState bishops, BitBoardState empty)
    {
        return BitBoardOperations::oneStepNorthWest(Ray::northWestOccluded(bishops, empty));
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