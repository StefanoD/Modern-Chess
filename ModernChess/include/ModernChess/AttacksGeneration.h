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

    namespace WhitePawnsAttack
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

        constexpr BitBoardState any(BitBoardState whitePawns)
        {
            return east(whitePawns) | west(whitePawns);
        }

        constexpr BitBoardState two(BitBoardState whitePawns)
        {
            return east(whitePawns) & west(whitePawns);
        }

        constexpr BitBoardState single(BitBoardState whitePawns)
        {
            return east(whitePawns) ^ west(whitePawns);
        }
    }

    namespace BlackPawnsAttack
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

        constexpr BitBoardState any(BitBoardState blackPawns)
        {
            return east(blackPawns) | west(blackPawns);
        }

        constexpr BitBoardState two(BitBoardState blackPawns)
        {
            return east(blackPawns) & west(blackPawns);
        }

        constexpr BitBoardState single(BitBoardState blackPawns)
        {
            return east(blackPawns) ^ west(blackPawns);
        }
    }

    namespace WhitePawnsQueries
    {
        // See https://www.chessprogramming.org/Pawn_Attacks_(Bitboards)

        constexpr bool ableToCaptureEast(BitBoardState whitePawns, BitBoardState blackFigures)
        {
            return (whitePawns & BlackPawnsAttack::west(blackFigures)) != 0;
        }

        constexpr bool ableToCaptureWest(BitBoardState whitePawns, BitBoardState blackFigures)
        {
            return (whitePawns & BlackPawnsAttack::east(blackFigures)) != 0;
        }

        constexpr bool ableToCaptureAny(BitBoardState whitePawns, BitBoardState blackFigures)
        {
            return (whitePawns & BlackPawnsAttack::any(blackFigures)) != 0;
        }

        /**
         * @brief A kind if of set-wise static exchange evaluation - only considering pawn-attacks from both sides.
         *        A square is assumed safe, if the number of own pawn defends if greater or equal than opponent
         *        pawn attacks. That is true if the own side defends a square twice, or the opposite side has no
         *        attacks at all, or own side attacks once and opponent not twice.
         * @param whitePawns
         * @param blackPawns
         * @return true if white pawns are on safe square, false otherwise
         */
        constexpr bool onSafePawnSquares(BitBoardState whitePawns, BitBoardState blackPawns)
        {
            const BitBoardState whitePawnsEastAttacks =  WhitePawnsAttack::east(whitePawns);
            const BitBoardState whitePawnsWestAttacks =  WhitePawnsAttack::west(whitePawns);
            const BitBoardState blackPawnsEastAttacks =  BlackPawnsAttack::east(blackPawns);
            const BitBoardState blackPawnsWestAttacks =  BlackPawnsAttack::west(blackPawns);
            const BitBoardState whitePawnsTwiceAttacks  = whitePawnsEastAttacks & whitePawnsWestAttacks;
            const BitBoardState whitePawnsSingleAttacks  = whitePawnsEastAttacks ^ whitePawnsWestAttacks;
            const BitBoardState blackPawnsTwiceAttacks  = blackPawnsEastAttacks & blackPawnsWestAttacks;
            const BitBoardState blackPawnsAnyAttacks  = blackPawnsEastAttacks | blackPawnsWestAttacks;
            return (whitePawnsTwiceAttacks | ~blackPawnsAnyAttacks | (whitePawnsSingleAttacks & ~blackPawnsTwiceAttacks)) != 0;
        }
    }

    namespace BlackPawnsQueries
    {
        // See https://www.chessprogramming.org/Pawn_Attacks_(Bitboards)

        constexpr bool ableToCaptureEast(BitBoardState blackPawns, BitBoardState whiteFigures)
        {
            return (blackPawns & WhitePawnsAttack::west(whiteFigures)) != 0;
        }

        constexpr bool ableToCaptureWest(BitBoardState blackPawns, BitBoardState whiteFigures)
        {
            return (blackPawns & WhitePawnsAttack::east(whiteFigures)) != 0;
        }

        constexpr bool ableToCaptureAny(BitBoardState blackPawns, BitBoardState whiteFigures)
        {
            return (blackPawns & WhitePawnsAttack::any(whiteFigures)) != 0;
        }

        /**
         * @brief A kind if of set-wise static exchange evaluation - only considering pawn-attacks from both sides.
         *        A square is assumed safe, if the number of own pawn defends if greater or equal than opponent
         *        pawn attacks. That is true if the own side defends a square twice, or the opposite side has no
         *        attacks at all, or own side attacks once and opponent not twice.
         * @param blackPawns
         * @param whitePawns
         * @return true if black pawns are on safe square, false otherwise
         */
        constexpr bool onSafePawnSquares(BitBoardState blackPawns, BitBoardState whitePawns)
        {
            // TODO Should maybe be tested
            const BitBoardState whitePawnsEastAttacks =  WhitePawnsAttack::east(whitePawns);
            const BitBoardState whitePawnsWestAttacks =  WhitePawnsAttack::west(whitePawns);
            const BitBoardState whitePawnsAnyAttacks  = whitePawnsEastAttacks | whitePawnsWestAttacks;
            const BitBoardState whitePawnsTwiceAttacks  = whitePawnsEastAttacks & whitePawnsWestAttacks;

            const BitBoardState blackPawnsEastAttacks =  BlackPawnsAttack::east(blackPawns);
            const BitBoardState blackPawnsWestAttacks =  BlackPawnsAttack::west(blackPawns);
            const BitBoardState blackPawnsSingleAttacks  = blackPawnsEastAttacks ^ blackPawnsWestAttacks;
            const BitBoardState blackPawnsTwiceAttacks  = blackPawnsEastAttacks & blackPawnsWestAttacks;
            return (blackPawnsTwiceAttacks | ~whitePawnsAnyAttacks | (blackPawnsSingleAttacks & ~whitePawnsTwiceAttacks)) != 0;
        }
    }

    namespace Knights
    {
        // See https://www.chessprogramming.org/Knight_Pattern#MultipleKnightAttacks
        constexpr BitBoardState attack(BitBoardState knights)
        {
            const BitBoardState l1 = (knights >> 1) & BitBoardConstants::notHFile;
            const BitBoardState l2 = (knights >> 2) & BitBoardConstants::notGHFile;
            const BitBoardState r1 = (knights << 1) & BitBoardConstants::notAFile;
            const BitBoardState r2 = (knights << 2) & BitBoardConstants::notABFile;
            const BitBoardState h1 = l1 | r1;
            const BitBoardState h2 = l2 | r2;
            return (h1 << 16) | (h1 >> 16) | (h2 << 8) | (h2 >> 8);
        }

        // See https://www.chessprogramming.org/Knight_Pattern#Knight_Forks
        /**
         * @brief The intersection of those targets with squares not occupied by own pieces or attacked by opponent
         *        pawns and knights, but attacked by own knight(s) leaves a move target set with some forced properties.
         * @param targets
         * @return
         */
        constexpr BitBoardState forkTargetSquare(BitBoardState targets) 
        {
            BitBoardState west = MoveGenerations::oneStepWest(targets);
            BitBoardState east = MoveGenerations::oneStepEast(targets);
            BitBoardState attack = east << 16;
            BitBoardState forks = (west << 16) & attack;
            attack |=  west << 16;
            forks |= (east >> 16) & attack;
            attack |=  east >> 16;
            forks |= (west >> 16) & attack;
            attack |=  west >> 16;
            east   = MoveGenerations::oneStepEast(east);
            west   = MoveGenerations::oneStepWest(west);
            forks |= (east <<  8) & attack;
            attack |=  east << 8;
            forks |= (west <<  8) & attack;
            attack |=  west << 8;
            forks |= (east >>  8) & attack;
            attack |=  east >> 8;
            forks |= (west >>  8) & attack;
            return forks;
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