#pragma once

#include "BitBoardConstants.h"
#include "BitBoardOperations.h"
#include "Square.h"

namespace ModernChess::AttacksGeneration
{
    // Attack calculations on an empty board.
    // See https://www.chessprogramming.org/On_an_empty_Board and
    // https://www.chessprogramming.org/Kogge-Stone_Algorithm

    constexpr BitBoardState fillUpOccluded(BitBoardState pieceBoard, BitBoardState emptySquaresBoard)
    {
        pieceBoard |= emptySquaresBoard & (pieceBoard << 8);
        emptySquaresBoard &= (emptySquaresBoard << 8);
        pieceBoard |= emptySquaresBoard & (pieceBoard << 16);
        emptySquaresBoard &= (emptySquaresBoard << 16);
        pieceBoard |= emptySquaresBoard & (pieceBoard << 32);
        return pieceBoard;
    }

    constexpr BitBoardState northOccluded(BitBoardState pieceBoard, BitBoardState emptySquaresBoard)
    {
        pieceBoard |= emptySquaresBoard & (pieceBoard << 8);
        emptySquaresBoard &= (emptySquaresBoard << 8);
        pieceBoard |= emptySquaresBoard & (pieceBoard << 16);
        emptySquaresBoard &= (emptySquaresBoard << 16);
        pieceBoard |= emptySquaresBoard & (pieceBoard << 32);
        return pieceBoard;
    }

    constexpr BitBoardState southOccluded(BitBoardState gen, BitBoardState pro)
    {
        gen |= pro & (gen >>  8);
        pro &=       (pro >>  8);
        gen |= pro & (gen >> 16);
        pro &=       (pro >> 16);
        gen |= pro & (gen >> 32);
        return gen;
    }

    constexpr BitBoardState eastOccluded(BitBoardState gen, BitBoardState pro)
    {
        pro &= BitBoardConstants::notAFile;
        gen |= pro & (gen << 1);
        pro &=       (pro << 1);
        gen |= pro & (gen << 2);
        pro &=       (pro << 2);
        gen |= pro & (gen << 4);
        return gen;
    }

    constexpr BitBoardState northEastOccluded(BitBoardState gen, BitBoardState pro)
    {
        pro &= BitBoardConstants::notAFile;
        gen |= pro & (gen <<  9);
        pro &=       (pro <<  9);
        gen |= pro & (gen << 18);
        pro &=       (pro << 18);
        gen |= pro & (gen << 36);
        return gen;
    }

    constexpr BitBoardState southEastOccluded(BitBoardState gen, BitBoardState pro)
    {
        pro &= BitBoardConstants::notAFile;
        gen |= pro & (gen >>  7);
        pro &=       (pro >>  7);
        gen |= pro & (gen >> 14);
        pro &=       (pro >> 14);
        gen |= pro & (gen >> 28);
        return gen;
    }

    constexpr BitBoardState westOccluded(BitBoardState gen, BitBoardState pro)
    {
        pro &= BitBoardConstants::notHFile;
        gen |= pro & (gen >> 1);
        pro &=       (pro >> 1);
        gen |= pro & (gen >> 2);
        pro &=       (pro >> 2);
        gen |= pro & (gen >> 4);
        return gen;
    }

    constexpr BitBoardState southWestOccluded(BitBoardState gen, BitBoardState pro)
    {
        pro &= BitBoardConstants::notHFile;
        gen |= pro & (gen >>  9);
        pro &=       (pro >>  9);
        gen |= pro & (gen >> 18);
        pro &=       (pro >> 18);
        gen |= pro & (gen >> 36);
        return gen;
    }

    constexpr BitBoardState northWestOccluded(BitBoardState gen, BitBoardState pro)
    {
        pro &= BitBoardConstants::notHFile;
        gen |= pro & (gen <<  7);
        pro &=       (pro <<  7);
        gen |= pro & (gen << 14);
        pro &=       (pro << 14);
        gen |= pro & (gen << 28);
        return gen;
    }

    constexpr BitBoardState northAttacks(BitBoardState rooks, BitBoardState empty)
    {
        return BitBoardOperations::oneStepNorth(northOccluded(rooks, empty));
    }
    
    BitBoardState southAttacks (BitBoardState rooks,   BitBoardState empty)
    {
        return BitBoardOperations::oneStepSouth(southOccluded(rooks, empty));
    }

    BitBoardState eastAttacks (BitBoardState rooks,   BitBoardState empty)
    {
        return BitBoardOperations::oneStepEast(eastOccluded(rooks,   empty));
    }

    BitBoardState northEastAttacks (BitBoardState bishops, BitBoardState empty)
    {
        return BitBoardOperations::oneStepNorthEast(northEastOccluded(bishops, empty));
    }

    BitBoardState southEastAttacks (BitBoardState bishops, BitBoardState empty)
    {
        return BitBoardOperations::oneStepSouthEast(southEastOccluded(bishops, empty));
    }

    BitBoardState westAttacks (BitBoardState rooks,   BitBoardState empty)
    {
        return BitBoardOperations::oneStepWest(westOccluded(rooks,   empty));
    }

    BitBoardState soutWestAttacks (BitBoardState bishops, BitBoardState empty)
    {
        return BitBoardOperations::oneStepSouthWest(southWestOccluded(bishops, empty));
    }

    BitBoardState northWestAttacks (BitBoardState bishops, BitBoardState empty)
    {
        return BitBoardOperations::oneStepNorthWest(northWestOccluded(bishops, empty));
    }

    
    constexpr BitBoardState northFill(BitBoardState gen)
    {
        gen |= (gen <<  8);
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