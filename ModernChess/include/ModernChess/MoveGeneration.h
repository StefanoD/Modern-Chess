#pragma once

#include "AttackQueries.h"
#include "GameState.h"
#include "OneStepMoves.h"
#include "BitBoardOperations.h"
#include "Move.h"

#include <vector>
#include <functional>

namespace ModernChess::MoveGenerations {
    class MoveGeneration {
    public:
        static void generateWhiteFigureMoves(const GameState &gameState, std::vector<Move> &movesToBeGenerated)
        {
            // loop over all the bitboards
            for (Figure piece = Figure::WhitePawn; piece < Figure::None; ++piece)
            {
                // init piece bitboard copy
                BitBoardState bitboard = gameState.board.bitboards[piece];

                // generate white pawns & white king castling moves

                // pick up white pawn bitboards index
                if (piece == Figure::WhitePawn)
                {
                    // loop over white pawns within white pawn bitboard
                    while (bitboard != BoardState::empty)
                    {
                        const Square sourceSquare = BitBoardOperations::bitScanForward(bitboard);
                        // White pawns are moving towards north direction
                        Square targetSquare =  BitBoardOperations::getNorthSquareFromGivenSquare(sourceSquare);

                        // generate quite pawn moves
                        if (const bool targetSquareIsOnBoard = (targetSquare <= Square::h8);
                            targetSquareIsOnBoard &&
                            !BitBoardOperations::isOccupied(gameState.board.occupancies[Color::Both], targetSquare))
                        {
                            // pawn promotion
                            if (sourceSquare >= a7 && sourceSquare <= h7)
                            {
                                movesToBeGenerated.emplace_back(sourceSquare, targetSquare, piece, Figure::WhiteQueen, false, false, false, false);
                                movesToBeGenerated.emplace_back(sourceSquare, targetSquare, piece, Figure::WhiteRook, false, false, false, false);
                                movesToBeGenerated.emplace_back(sourceSquare, targetSquare, piece, Figure::WhiteBishop, false, false, false, false);
                                movesToBeGenerated.emplace_back(sourceSquare, targetSquare, piece, Figure::WhiteKnight, false, false, false, false);
                            }
                            else
                            {
                                // single pawn push
                                movesToBeGenerated.emplace_back(sourceSquare, targetSquare, piece, Figure::None, false, false, false, false);

                                // double pawn push
                                if ((sourceSquare >= a2 && sourceSquare <= h2) &&
                                    !BitBoardOperations::isOccupied(gameState.board.occupancies[Color::Both], BitBoardOperations::getNorthSquareFromGivenSquare(targetSquare)))
                                {
                                    movesToBeGenerated.emplace_back(sourceSquare, BitBoardOperations::getNorthSquareFromGivenSquare(targetSquare), piece, Figure::None, false, true, false, false);
                                }
                            }
                        }

                        // init pawn attacks of bitboard and generate pawn captures
                        for (BitBoardState attacks = AttackQueries::pawnAttackTable[Color::White][sourceSquare] & gameState.board.occupancies[Color::Black];
                             attacks != BoardState::empty;
                             attacks = BitBoardOperations::eraseSquare(attacks, targetSquare))
                        {
                            // init target square
                            targetSquare = BitBoardOperations::bitScanForward(attacks);

                            // pawn promotion
                            if (sourceSquare >= a7 && sourceSquare <= h7)
                            {
                                movesToBeGenerated.emplace_back(sourceSquare, targetSquare, piece, Figure::WhiteQueen, true, false, false, false);
                                movesToBeGenerated.emplace_back(sourceSquare, targetSquare, piece, Figure::WhiteRook, true, false, false, false);
                                movesToBeGenerated.emplace_back(sourceSquare, targetSquare, piece, Figure::WhiteBishop, true, false, false, false);
                                movesToBeGenerated.emplace_back(sourceSquare, targetSquare, piece, Figure::WhiteKnight, true, false, false, false);
                            }
                            else
                            {
                                // one square ahead pawn move
                                movesToBeGenerated.emplace_back(sourceSquare, targetSquare, piece, Figure::None, true, false, false, false);
                            }
                        }

                        // generate en passant captures
                        if (gameState.enPassantTarget != Square::undefined)
                        {
                            // lookup pawn attacks and bitwise AND with en passant square (bit)
                            const BitBoardState enPassantAttacks = AttackQueries::pawnAttackTable[Color::White][sourceSquare] & BitBoardOperations::occupySquare(BoardState::empty, gameState.enPassantTarget);

                            // make sure en passant capture possible
                            if (enPassantAttacks != BoardState::empty)
                            {
                                // init en passant capture target square
                                const Square targetEnPassant = BitBoardOperations::bitScanForward(enPassantAttacks);
                                movesToBeGenerated.emplace_back(sourceSquare, targetEnPassant, piece, Figure::None, true, false, true, false);
                            }
                        }

                        // pop ls1b from piece bitboard copy
                        bitboard = BitBoardOperations::eraseSquare(bitboard, sourceSquare);
                    }
                }
                else if (piece == Figure::WhiteKing)
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
                                movesToBeGenerated.emplace_back(Square::e1, Square::g1, piece, Figure::None, false, false, false, true);
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
                            if (!AttackQueries::squareIsAttackedByBlack(gameState.board,e1) &&
                                !AttackQueries::squareIsAttackedByBlack(gameState.board, d1))
                            {
                                movesToBeGenerated.emplace_back(Square::e1, Square::c1, piece, Figure::None, false, false, false, true);
                            }
                        }
                    }
                }
                else if (piece == Figure::WhiteKnight)
                {
                    // loop over source squares of piece bitboard copy
                    while (bitboard != BoardState::empty)
                    {
                        const Square sourceSquare = BitBoardOperations::bitScanForward(bitboard);

                        // init piece attacks in order to get set of target squares
                        BitBoardState attacks = AttackQueries::knightAttackTable[sourceSquare] & (~gameState.board.occupancies[Color::White]);

                        // loop over target squares available from generated attacks
                        while (attacks != BoardState::empty)
                        {
                            // init target square
                            const Square targetSquare = BitBoardOperations::bitScanForward(attacks);

                            if (BitBoardOperations::isOccupied(gameState.board.occupancies[Color::Black], targetSquare))
                            {
                                // capture move
                                movesToBeGenerated.emplace_back(sourceSquare, targetSquare, piece, Figure::None, true, false, false, false);
                            }
                            else
                            {
                                // quite move
                                movesToBeGenerated.emplace_back(sourceSquare, targetSquare, piece, Figure::None, false, false, false, false);
                            }
                            // pop ls1b in current attacks set
                            attacks = BitBoardOperations::eraseSquare(attacks, targetSquare);
                        }

                        // pop ls1b of the current piece bitboard copy
                        bitboard = BitBoardOperations::eraseSquare(bitboard, sourceSquare);
                    }
                }
                else if (piece == Figure::WhiteBishop)
                {
                    // loop over source squares of piece bitboard copy
                    while (bitboard != BoardState::empty)
                    {
                        const Square sourceSquare = BitBoardOperations::bitScanForward(bitboard);

                        // init piece attacks in order to get set of target squares
                        BitBoardState attacks = AttackQueries::bishopAttacks.getAttacks(sourceSquare, gameState.board.occupancies[Color::Both]) & (~gameState.board.occupancies[Color::White]);

                        // loop over target squares available from generated attacks
                        while (attacks != BoardState::empty)
                        {
                            // init target square
                            const Square targetSquare = BitBoardOperations::bitScanForward(attacks);

                            if (BitBoardOperations::isOccupied(gameState.board.occupancies[Color::Black], targetSquare))
                            {
                                // capture move
                                movesToBeGenerated.emplace_back(sourceSquare, targetSquare, piece, Figure::None, true, false, false, false);
                            }
                            else
                            {
                                // quite move
                                movesToBeGenerated.emplace_back(sourceSquare, targetSquare, piece, Figure::None, false, false, false, false);
                            }


                            // pop ls1b in current attacks set
                            attacks = BitBoardOperations::eraseSquare(attacks, targetSquare);
                        }

                        // pop ls1b of the current piece bitboard copy
                        bitboard = BitBoardOperations::eraseSquare(bitboard, sourceSquare);
                    }
                }
            }
        }

    private:
        static BitBoardState generateWhitePieceMoves(const GameState &gameState,
                                            std::vector<Move> &movesToBeGenerated,
                                            Figure piece,
                                            BitBoardState bitboard,
                                            const std::function<BitBoardState(Square)>& getAttacks)
        {
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
                        movesToBeGenerated.emplace_back(sourceSquare, targetSquare, piece, Figure::None, true, false, false, false);
                    }
                    else
                    {
                        // quite move
                        movesToBeGenerated.emplace_back(sourceSquare, targetSquare, piece, Figure::None, false, false, false, false);
                    }

                    // pop ls1b in current attacks set
                    attacks = BitBoardOperations::eraseSquare(attacks, targetSquare);
                }

                // pop ls1b of the current piece bitboard copy
                bitboard = BitBoardOperations::eraseSquare(bitboard, sourceSquare);
            }

            // return new bitboard state
            return bitboard;
        }
    };
}