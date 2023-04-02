#pragma once

#include "BitBoardConstants.h"
#include "ModernChess/BitBoardOperations.h"
#include "MoveGenerations.h"
#include "Square.h"

namespace ModernChess::AttackGeneration::SlidingPieces {

    // mask bishop attacks
    constexpr BitBoardState maskBishopAttacks(Square square)
    {
        // result attacks bitboard
        BitBoardState attacks = BoardState::empty;

        // init target rank & files
        const int targetRank = square / 8;
        int const targetFile = square % 8;

        // init ranks and files
        int rank;
        int file;

        // mask relevant bishop occupancy bits
        for (rank = targetRank + 1, file = targetFile + 1; rank <= 6 && file <= 6; ++rank, ++file)
        {
            const Square attackedSquare = BitBoardOperations::getSquare(rank, file);
            attacks = BitBoardOperations::occupySquare(attacks, attackedSquare);
        }

        for (rank = targetRank - 1, file = targetFile + 1; rank >= 1 && file <= 6; --rank, ++file)
        {
            const Square attackedSquare = BitBoardOperations::getSquare(rank, file);
            attacks = BitBoardOperations::occupySquare(attacks, attackedSquare);
        }

        for (rank = targetRank + 1, file = targetFile - 1; rank <= 6 && file >= 1; ++rank, --file)
        {
            const Square attackedSquare = BitBoardOperations::getSquare(rank, file);
            attacks = BitBoardOperations::occupySquare(attacks, attackedSquare);
        }

        for (rank = targetRank - 1, file = targetFile - 1; rank >= 1 && file >= 1; --rank, --file)
        {
            const Square attackedSquare = BitBoardOperations::getSquare(rank, file);
            attacks = BitBoardOperations::occupySquare(attacks, attackedSquare);
        }

        // return attack map
        return attacks;
    }

    // generate bishop attacks on the fly
    constexpr BitBoardState bishopAttacksOnTheFly(BitBoardState occupiedSquares, Square square)
    {
        // result attacks bitboard
        BitBoardState attacks = BoardState::empty;

        // init target rank & files
        const int targetRank = square / 8;
        const int targetFile = square % 8;

        // init ranks & files
        int rank;
        int file;

        // generate bishop attacks
        for (rank = targetRank + 1, file = targetFile + 1; rank <= 7 && file <= 7; ++rank, ++file)
        {
            const Square attackedSquare = BitBoardOperations::getSquare(rank, file);
            attacks = BitBoardOperations::occupySquare(attacks, attackedSquare);

            if (BitBoardOperations::isOccupied(occupiedSquares, attackedSquare))
            {
                break;
            }
        }

        for (rank = targetRank - 1, file = targetFile + 1; rank >= 0 && file <= 7; --rank, ++file)
        {
            const Square attackedSquare = BitBoardOperations::getSquare(rank, file);
            attacks = BitBoardOperations::occupySquare(attacks, attackedSquare);

            if (BitBoardOperations::isOccupied(occupiedSquares, attackedSquare))
            {
                break;
            }
        }

        for (rank = targetRank + 1, file = targetFile - 1; rank <= 7 && file >= 0; ++rank, --file)
        {
            const Square attackedSquare = BitBoardOperations::getSquare(rank, file);
            attacks = BitBoardOperations::occupySquare(attacks, attackedSquare);

            if (BitBoardOperations::isOccupied(occupiedSquares, attackedSquare))
            {
                break;
            }
        }

        for (rank = targetRank - 1, file = targetFile - 1; rank >= 0 && file >= 0; --rank, --file)
        {
            const Square attackedSquare = BitBoardOperations::getSquare(rank, file);
            attacks = BitBoardOperations::occupySquare(attacks, attackedSquare);

            if (BitBoardOperations::isOccupied(occupiedSquares, attackedSquare))
            {
                break;
            }
        }

        // return attack map
        return attacks;
    }

    // mask rook attacks
    constexpr BitBoardState maskRookAttacks(Square square)
    {
        // result attacks bitboard
        BitBoardState attacks = BoardState::empty;

        // init target rank & files
        const int targetRank = square / 8;
        const int targetFile = square % 8;

        // init ranks & files
        int rank;
        int file;

        // mask relevant bishop occupancy bits
        for (rank = targetRank + 1; rank <= 6; ++rank)
        {
            const Square attackedSquare = BitBoardOperations::getSquare(rank, targetFile);
            attacks = BitBoardOperations::occupySquare(attacks, attackedSquare);
        }

        for (rank = targetRank - 1; rank >= 1; --rank)
        {
            const Square attackedSquare = BitBoardOperations::getSquare(rank, targetFile);
            attacks = BitBoardOperations::occupySquare(attacks, attackedSquare);
        }

        for (file = targetFile + 1; file <= 6; ++file)
        {
            const Square attackedSquare = BitBoardOperations::getSquare(targetRank, file);
            attacks = BitBoardOperations::occupySquare(attacks, attackedSquare);
        }

        for (file = targetFile - 1; file >= 1; --file)
        {
            const Square attackedSquare = BitBoardOperations::getSquare(targetRank, file);
            attacks = BitBoardOperations::occupySquare(attacks, attackedSquare);
        }

        // return attack map
        return attacks;
    }

    // generate rook attacks on the fly
    constexpr BitBoardState rookAttacksOnTheFly(BitBoardState occupiedSquares, Square square)
    {
        // result attacks bitboard
        BitBoardState attacks = BoardState::empty;

        // init target rank & files
        const int targetRank = square / 8;
        const int targetFile = square % 8;

        // init ranks & files
        int rank;
        int file;

        // generate rook attacks
        for (rank = targetRank + 1; rank <= 7; ++rank)
        {
            const Square attackedSquare = BitBoardOperations::getSquare(rank, targetFile);
            attacks = BitBoardOperations::occupySquare(attacks, attackedSquare);

            if (BitBoardOperations::isOccupied(occupiedSquares, attackedSquare))
            {
                break;
            }
        }

        for (rank = targetRank - 1; rank >= 0; --rank)
        {
            const Square attackedSquare = BitBoardOperations::getSquare(rank, targetFile);
            attacks = BitBoardOperations::occupySquare(attacks, attackedSquare);

            if (BitBoardOperations::isOccupied(occupiedSquares, attackedSquare))
            {
                break;
            }
        }

        for (file = targetFile + 1; file <= 7; ++file)
        {
            const Square attackedSquare = BitBoardOperations::getSquare(targetRank, file);
            attacks = BitBoardOperations::occupySquare(attacks, attackedSquare);

            if (BitBoardOperations::isOccupied(occupiedSquares, attackedSquare))
            {
                break;
            }
        }

        for (file = targetFile - 1; file >= 0; --file)
        {
            const Square attackedSquare = BitBoardOperations::getSquare(targetRank, file);
            attacks = BitBoardOperations::occupySquare(attacks, attackedSquare);

            if (BitBoardOperations::isOccupied(occupiedSquares, attackedSquare))
            {
                break;
            }
        }

        // return attack map
        return attacks;
    }


        /*BitBoardState attack_table[...]; // ~840 KiB all rook and bishop attacks, less with constructive collisions optimization

        struct SMagic {
            BitBoardState* ptr;  // pointer to attack_table for each particular square
            BitBoardState mask;  // to mask relevant squares of both lines (no outer squares)
            BitBoardState magic; // magic 64-bit factor
            int shift; // shift right
        };

        SMagic mBishopTbl[64];
        SMagic mRookTbl[64];

        BitBoardState bishopAttacks(BitBoardState occ, BitBoardState sq) {
            BitBoardState* aptr = mBishopTbl[sq].ptr;
            occ      &= mBishopTbl[sq].mask;
            occ      *= mBishopTbl[sq].magic;
            occ     >>= mBishopTbl[sq].shift;
            return aptr[occ];
        }

        BitBoardState rookAttacks(BitBoardState occ, Square sq) {
            BitBoardState* aptr = mRookTbl[sq].ptr;
            occ      &= mRookTbl[sq].mask;
            occ      *= mRookTbl[sq].magic;
            occ     >>= mRookTbl[sq].shift;
            return aptr[occ];
        }*/
    }