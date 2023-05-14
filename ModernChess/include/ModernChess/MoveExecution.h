#pragma once

#include "GameState.h"
#include "BitBoardOperations.h"
#include "AttackQueries.h"

namespace ModernChess::MoveGenerations
{
    enum class MoveType
    {
        AllMoves,
        CapturesOnly
    };

    class MoveExecution
    {
    public:
        MoveExecution() = delete;

        static bool executeMoveForWhite(GameState &gameState, Move move, MoveType moveType)
        {
            // make quiet and/or capture move
            if (moveType == MoveType::AllMoves or move.isCapture())
            {
                // preserve board state
                const Board boardCopy = gameState.board;

                // parse move
                const Square sourceSquare = move.getFrom();
                const Square targetSquare = move.getTo();
                const Figure movedFigure = move.getMovedFigure();
                const bool castling = move.isCastlingMove();

                // move movedFigure
                removeFromBitboards(gameState, movedFigure, Color::White, sourceSquare);
                addToBitboards(gameState, movedFigure, Color::White, targetSquare);

                // handling capture moves
                if (move.isCapture())
                {
                    removeCapturedFigure(gameState, Figure::BlackPawn, Figure::BlackKing, Color::Black, targetSquare);
                }

                // handle pawn promotions
                if (const Figure promotedPiece = move.getPromotedPiece();
                        promotedPiece != Figure::None)
                {
                    // erase the pawn from the target square
                    removeFromBitboards(gameState, Figure::WhitePawn, Color::White, targetSquare);
                    // set up promoted movedFigure on chess board
                    addToBitboards(gameState, promotedPiece, Color::White, targetSquare);
                }

                // handle en passant captures
                if (move.isEnPassantCapture())
                {
                    // The en passant capture is always one behind a double pawn push from the opponent
                    const Square actualPawnSquare = BitBoardOperations::getSouthSquareFromGivenSquare(targetSquare);
                    removeFromBitboards(gameState, Figure::BlackPawn, Color::Black, actualPawnSquare);
                }

                // reset en passant square
                gameState.board.enPassantTarget = Square::undefined;

                // handle double pawn push
                if (move.isDoublePawnPush())
                {
                    gameState.board.enPassantTarget = BitBoardOperations::getSouthSquareFromGivenSquare(targetSquare);
                }

                // handle castling moves
                if (castling)
                {
                    switch (targetSquare)
                    {
                        case (Square::g1):
                            // white castles king side --> move H rook
                            removeFromBitboards(gameState, Figure::WhiteRook, Color::White, Square::h1);
                            addToBitboards(gameState, Figure::WhiteRook, Color::White, Square::f1);
                            break;

                        case (Square::c1):
                            // white castles queen side --> move A rook
                            removeFromBitboards(gameState, Figure::WhiteRook, Color::White, Square::a1);
                            addToBitboards(gameState, Figure::WhiteRook, Color::White, Square::d1);
                            break;
                        default:
                            // TODO throw exception
                            break;
                    }
                }

                // make sure that king has not been exposed into a check
                if (const Square kingsSquare = BitBoardOperations::bitScanForward(gameState.board.bitboards[Figure::WhiteKing]);
                        AttackQueries::squareIsAttackedByBlack(gameState.board, kingsSquare))
                {
                    // take move back
                    gameState.board = boardCopy;

                    // return illegal move
                    return false;
                }

                // update castling rights
                gameState.board.castlingRights = updateCastlingRights(gameState.board.castlingRights, sourceSquare, targetSquare);
                // change side to move
                gameState.board.sideToMove = Color(!bool(gameState.board.sideToMove));

                // return legal move
                return true;
            }

            // move type is not MoveType::AllMoves and the move is also not a capture --> don't make it
            return false;
        }
    private:
        static void removeCapturedFigure(GameState &gameState, Figure bitBoardStart, Figure bitBoardEnd, Color opponentsColor, Square targetSquare)
        {
            // loop over bitboards opposite to the current side to move
            for (Figure figure = bitBoardStart; figure <= bitBoardEnd; ++figure)
            {
                // if there's a figure on the target square
                if (BitBoardOperations::isOccupied(gameState.board.bitboards[figure], targetSquare))
                {
                    // remove it from opponents bitboard
                    removeFromBitboards(gameState, figure, opponentsColor, targetSquare);
                    break;
                }
            }
        }

        static void removeFromBitboards(GameState &gameState, Figure figure, Color color, Square square)
        {
            gameState.board.bitboards[figure] = BitBoardOperations::eraseSquare(gameState.board.bitboards[figure], square);
            gameState.board.occupancies[color] = BitBoardOperations::eraseSquare(gameState.board.occupancies[color], square);
            gameState.board.occupancies[Color::Both] = BitBoardOperations::eraseSquare(gameState.board.occupancies[Color::Both], square);
        }

        static void addToBitboards(GameState &gameState, Figure figure, Color color, Square square)
        {
            gameState.board.bitboards[figure] = BitBoardOperations::occupySquare(gameState.board.bitboards[figure], square);
            gameState.board.occupancies[color] = BitBoardOperations::occupySquare(gameState.board.occupancies[color], square);
            gameState.board.occupancies[Color::Both] = BitBoardOperations::occupySquare(gameState.board.occupancies[Color::Both], square);
        }
    };
}