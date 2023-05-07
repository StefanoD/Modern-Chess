#pragma once

#include "AttackQueries.h"
#include "GameState.h"
#include "OneStepMoves.h"
#include "BitBoardOperations.h"
#include "Move.h"

#include <vector>
#include <functional>
#include <array>

namespace ModernChess::MoveGenerations {
    class MoveGeneration
    {
        static constexpr std::array<Figure, 6> whiteFigures{
                Figure::WhitePawn,
                Figure::WhiteKnight,
                Figure::WhiteBishop,
                Figure::WhiteRook,
                Figure::WhiteQueen,
                Figure::WhiteKing
        };

        static constexpr std::array<Figure, 6> blackFigures{
                Figure::BlackPawn,
                Figure::BlackKnight,
                Figure::BlackBishop,
                Figure::BlackRook,
                Figure::BlackQueen,
                Figure::BlackKing
        };
    public:
        static void generateWhiteFigureMoves(const GameState &gameState, std::vector<Move> &movesToBeGenerated)
        {
            // loop over all the white bitboards
            for (const Figure figure: whiteFigures)
            {
                if (figure == Figure::WhitePawn)
                {
                    // init figure bitboard copy
                    BitBoardState bitboard = gameState.board.bitboards[figure];

                    // loop over white pawns within white pawn bitboard
                    while (bitboard != BoardState::empty)
                    {
                        const Square sourceSquare = BitBoardOperations::bitScanForward(bitboard);
                        // White pawns are moving towards north direction
                        Square targetSquare = BitBoardOperations::getNorthSquareFromGivenSquare(sourceSquare);

                        // generate quite pawn moves
                        if (const bool targetSquareIsOnBoard = (targetSquare <= Square::h8);
                                targetSquareIsOnBoard &&
                                !BitBoardOperations::isOccupied(gameState.board.occupancies[Color::Both], targetSquare))
                        {
                            // pawn promotion
                            if (sourceSquare >= a7 && sourceSquare <= h7)
                            {
                                movesToBeGenerated.emplace_back(sourceSquare, targetSquare, figure, Figure::WhiteQueen,
                                                                false, false, false, false);
                                movesToBeGenerated.emplace_back(sourceSquare, targetSquare, figure, Figure::WhiteRook,
                                                                false, false, false, false);
                                movesToBeGenerated.emplace_back(sourceSquare, targetSquare, figure, Figure::WhiteBishop,
                                                                false, false, false, false);
                                movesToBeGenerated.emplace_back(sourceSquare, targetSquare, figure, Figure::WhiteKnight,
                                                                false, false, false, false);
                            }
                            else
                            {
                                // single pawn push
                                movesToBeGenerated.emplace_back(sourceSquare, targetSquare, figure, Figure::None, false,
                                                                false, false, false);

                                // double pawn push
                                if ((sourceSquare >= a2 && sourceSquare <= h2) &&
                                    !BitBoardOperations::isOccupied(gameState.board.occupancies[Color::Both],
                                                                    BitBoardOperations::getNorthSquareFromGivenSquare(
                                                                            targetSquare)))
                                {
                                    movesToBeGenerated.emplace_back(sourceSquare,
                                                                    BitBoardOperations::getNorthSquareFromGivenSquare(
                                                                            targetSquare), figure, Figure::None, false,
                                                                    true, false, false);
                                }
                            }
                        }

                        // init pawn attacks of bitboard and generate pawn captures
                        for (BitBoardState attacks = AttackQueries::pawnAttackTable[Color::White][sourceSquare] &
                                                     gameState.board.occupancies[Color::Black];
                             attacks != BoardState::empty;
                             attacks = BitBoardOperations::eraseSquare(attacks, targetSquare))
                        {
                            // init target square
                            targetSquare = BitBoardOperations::bitScanForward(attacks);

                            // pawn promotion
                            if (sourceSquare >= a7 && sourceSquare <= h7)
                            {
                                movesToBeGenerated.emplace_back(sourceSquare, targetSquare, figure, Figure::WhiteQueen,
                                                                true, false, false, false);
                                movesToBeGenerated.emplace_back(sourceSquare, targetSquare, figure, Figure::WhiteRook,
                                                                true, false, false, false);
                                movesToBeGenerated.emplace_back(sourceSquare, targetSquare, figure, Figure::WhiteBishop,
                                                                true, false, false, false);
                                movesToBeGenerated.emplace_back(sourceSquare, targetSquare, figure, Figure::WhiteKnight,
                                                                true, false, false, false);
                            }
                            else
                            {
                                // one square ahead pawn move
                                movesToBeGenerated.emplace_back(sourceSquare, targetSquare, figure, Figure::None, true,
                                                                false, false, false);
                            }
                        }

                        // generate en passant captures
                        if (gameState.enPassantTarget != Square::undefined)
                        {
                            // lookup pawn attacks and bitwise AND with en passant square (bit)
                            const BitBoardState enPassantAttacks =
                                    AttackQueries::pawnAttackTable[Color::White][sourceSquare] &
                                    BitBoardOperations::occupySquare(BoardState::empty, gameState.enPassantTarget);

                            // make sure en passant capture possible
                            if (enPassantAttacks != BoardState::empty)
                            {
                                // init en passant capture target square
                                const Square targetEnPassant = BitBoardOperations::bitScanForward(enPassantAttacks);
                                movesToBeGenerated.emplace_back(sourceSquare, targetEnPassant, figure, Figure::None,
                                                                true, false, true, false);
                            }
                        }

                        // pop ls1b from figure bitboard copy
                        bitboard = BitBoardOperations::eraseSquare(bitboard, sourceSquare);
                    }
                }
                else if (figure == Figure::WhiteKing)
                {
                    // king side castling is available
                    if (whiteCanCastleKingSide(gameState.castleRights))
                    {
                        // make sure square between king and king's rook are empty
                        if (!BitBoardOperations::isOccupied(gameState.board.occupancies[Color::Both], f1) &&
                            !BitBoardOperations::isOccupied(gameState.board.occupancies[Color::Both], g1))
                        {
                            // make sure king and the f1 squares are not under attacks.
                            // The g1 square will be checked in the makeMove() function due to performance reasons
                            if (!AttackQueries::squareIsAttackedByBlack(gameState.board, Square::e1) &&
                                !AttackQueries::squareIsAttackedByBlack(gameState.board, Square::f1))
                            {
                                movesToBeGenerated.emplace_back(Square::e1, Square::g1, figure, Figure::None, false,
                                                                false, false, true);
                            }
                        }
                    }

                    // queen side castling is available
                    if (whiteCanCastleQueenSide(gameState.castleRights))
                    {
                        // make sure square between king and queen's rook are empty
                        if (!BitBoardOperations::isOccupied(gameState.board.occupancies[Color::Both], d1) &&
                            !BitBoardOperations::isOccupied(gameState.board.occupancies[Color::Both], c1) &&
                            !BitBoardOperations::isOccupied(gameState.board.occupancies[Color::Both], b1))
                        {
                            // make sure king and the d1 squares are not under attacks
                            // The c1 square will be checked in the makeMove() function due to performance reasons
                            if (!AttackQueries::squareIsAttackedByBlack(gameState.board, e1) &&
                                !AttackQueries::squareIsAttackedByBlack(gameState.board, d1))
                            {
                                movesToBeGenerated.emplace_back(Square::e1, Square::c1, figure, Figure::None, false,
                                                                false, false, true);
                            }
                        }
                    }

                    std::function<BitBoardState(Square)> getAttacks = [&gameState](Square sourceSquare) {
                        return AttackQueries::kingAttackTable[sourceSquare] &
                               (~gameState.board.occupancies[Color::White]);
                    };

                    generateWhitePieceMoves(gameState, movesToBeGenerated, figure, std::move(getAttacks));
                }
                else if (figure == Figure::WhiteKnight)
                {
                    std::function<BitBoardState(Square)> getAttacks = [&gameState](Square sourceSquare) {
                        return AttackQueries::knightAttackTable[sourceSquare] &
                               (~gameState.board.occupancies[Color::White]);
                    };

                    generateWhitePieceMoves(gameState, movesToBeGenerated, figure, std::move(getAttacks));
                }
                else if (figure == Figure::WhiteBishop)
                {
                    std::function<BitBoardState(Square)> getAttacks = [&gameState](Square sourceSquare) {
                        return AttackQueries::bishopAttacks.getAttacks(sourceSquare,
                                                                       gameState.board.occupancies[Color::Both]) &
                               (~gameState.board.occupancies[Color::White]);
                    };

                    generateWhitePieceMoves(gameState, movesToBeGenerated, figure, std::move(getAttacks));
                }
                else if (figure == Figure::WhiteRook)
                {
                    std::function<BitBoardState(Square)> getAttacks = [&gameState](Square sourceSquare) {
                        return AttackQueries::rookAttacks.getAttacks(sourceSquare,
                                                                     gameState.board.occupancies[Color::Both]) &
                               (~gameState.board.occupancies[Color::White]);
                    };

                    generateWhitePieceMoves(gameState, movesToBeGenerated, figure, std::move(getAttacks));
                }
            }
        }

    private:
        static void generateWhitePieceMoves(const GameState &gameState,
                                            std::vector<Move> &movesToBeGenerated,
                                            Figure piece,
                                            std::function<BitBoardState(Square)> getAttacks)
        {
            BitBoardState bitboard = gameState.board.bitboards[piece];

            // loop over source squares of piece bitboard copy
            while (bitboard != BoardState::empty)
            {
                const Square sourceSquare = BitBoardOperations::bitScanForward(bitboard);

                // init piece attacks in order to get set of target squares
                BitBoardState attacks = getAttacks(sourceSquare);

                // loop over target squares available from generated attacks
                while (attacks != BoardState::empty)
                {
                    // init target square
                    const Square targetSquare = BitBoardOperations::bitScanForward(attacks);

                    if (BitBoardOperations::isOccupied(gameState.board.occupancies[Color::Black], targetSquare))
                    {
                        // capture move
                        movesToBeGenerated.emplace_back(sourceSquare, targetSquare, piece, Figure::None, true, false,
                                                        false, false);
                    }
                    else
                    {
                        // quiet move
                        movesToBeGenerated.emplace_back(sourceSquare, targetSquare, piece, Figure::None, false, false,
                                                        false, false);
                    }

                    // pop ls1b in current attacks set
                    attacks = BitBoardOperations::eraseSquare(attacks, targetSquare);
                }

                // pop ls1b of the current piece bitboard copy
                bitboard = BitBoardOperations::eraseSquare(bitboard, sourceSquare);
            }
        }
    };
}