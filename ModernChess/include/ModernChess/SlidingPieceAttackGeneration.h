#pragma once

#include "BitBoardConstants.h"
#include "MoveGenerations.h"
#include "Square.h"

namespace ModernChess::AttackGeneration::SlidingPieces
    {

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
            for (rank = targetRank + 1, file = targetFile + 1; rank <= 6 && file <= 6; rank++, file++)
            {
                attacks |= (1ULL << (rank * 8 + file));
            }

            for (rank = targetRank - 1, file = targetFile + 1; rank >= 1 && file <= 6; rank--, file++)
            {
                attacks |= (1ULL << (rank * 8 + file));
            }

            for (rank = targetRank + 1, file = targetFile - 1; rank <= 6 && file >= 1; rank++, file--)
            {
                attacks |= (1ULL << (rank * 8 + file));
            }

            for (rank = targetRank - 1, file = targetFile - 1; rank >= 1 && file >= 1; rank--, file--)
            {
                attacks |= (1ULL << (rank * 8 + file));
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