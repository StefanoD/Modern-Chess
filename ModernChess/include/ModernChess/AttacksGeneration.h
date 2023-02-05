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


    constexpr BitBoardState nortOccl(BitBoardState pieceBoard, BitBoardState emptySquaresBoard)
    {
        pieceBoard |= emptySquaresBoard & (pieceBoard << 8);
        emptySquaresBoard &= (emptySquaresBoard << 8);
        pieceBoard |= emptySquaresBoard & (pieceBoard << 16);
        emptySquaresBoard &= (emptySquaresBoard << 16);
        pieceBoard |= emptySquaresBoard & (pieceBoard << 32);
        return pieceBoard;
    }

    constexpr BitBoardState northFill(BitBoardState gen)
    {
        gen |= (gen <<  8);
        gen |= (gen << 16);
        gen |= (gen << 32);
        return gen;
    }

    constexpr BitBoardState northAttacks(BitBoardState rooks, BitBoardState empty)
    {
        return BitBoardOperations::oneStepNorth(nortOccl(rooks,   empty));
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