#pragma once

#include "GameState.h"
#include "BitBoardOperations.h"
#include "AttackQueries.h"

namespace ModernChess
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

        static bool executeMove(GameState &gameState, Move move, MoveType moveType)
        {
            if (gameState.board.sideToMove == Color::White)
            {
                return MoveExecution::executeMoveForWhite(gameState, move, moveType);
            }

            return MoveExecution::executeMoveForBlack(gameState, move, moveType);
        }

        static bool executeMoveForWhite(GameState &gameState, Move move, MoveType moveType)
        {
            // make quiet or capture move
            if (moveType == MoveType::AllMoves or move.isCapture())
            {
                // preserve board state
                const Board boardCopy = gameState.board;

                // parse move
                const Square sourceSquare = move.getFrom();
                const Square targetSquare = move.getTo();
                const Figure movedFigure = move.getMovedFigure();
                const bool castling = move.isCastlingMove();

                // handling capture moves
                if (move.isCapture())
                {
                    removeCapturedFigure(gameState, Figure::BlackPawn, Figure::BlackKing, Color::Black, targetSquare);
                }

                // Add the moved figure into bitboards after the potential capture has been removed, otherwise we
                // would potentially remove the moved figure again, if we go the other way around
                removeFromBitboards(gameState, movedFigure, Color::White, sourceSquare);
                addToBitboards(gameState, movedFigure, Color::White, targetSquare);

                handlePawnPromotion(gameState, move, Figure::WhitePawn, Color::White, targetSquare);

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
                gameState.board.sideToMove = Color::Black;

                // return legal move
                return true;
            }

            // Neither MoveType::AllMoves nor capture move --> won't be executed
            return false;
        }

        static bool executeMoveForBlack(GameState &gameState, Move move, MoveType moveType)
        {
            // make quiet or capture move
            if (moveType == MoveType::AllMoves or move.isCapture())
            {
                // preserve board state
                const Board boardCopy = gameState.board;

                // parse move
                const Square sourceSquare = move.getFrom();
                const Square targetSquare = move.getTo();
                const Figure movedFigure = move.getMovedFigure();
                const bool castling = move.isCastlingMove();

                // handling capture moves
                if (move.isCapture())
                {
                    removeCapturedFigure(gameState, Figure::WhitePawn, Figure::WhiteKing, Color::White, targetSquare);
                }

                // Add the moved figure into bitboards after the potential capture has been removed, otherwise we
                // would potentially remove the moved figure again, if we go the other way around
                removeFromBitboards(gameState, movedFigure, Color::Black, sourceSquare);
                addToBitboards(gameState, movedFigure, Color::Black, targetSquare);

                handlePawnPromotion(gameState, move, Figure::BlackPawn, Color::Black, targetSquare);

                // handle en passant captures
                if (move.isEnPassantCapture())
                {
                    // The en passant capture is always one behind a double pawn push from the opponent
                    const Square actualPawnSquare = BitBoardOperations::getNorthSquareFromGivenSquare(targetSquare);
                    removeFromBitboards(gameState, Figure::WhitePawn, Color::White, actualPawnSquare);
                }

                // reset en passant square
                gameState.board.enPassantTarget = Square::undefined;

                // handle double pawn push
                if (move.isDoublePawnPush())
                {
                    gameState.board.enPassantTarget = BitBoardOperations::getNorthSquareFromGivenSquare(targetSquare);
                }

                // handle castling moves
                if (castling)
                {
                    switch (targetSquare)
                    {
                        case (Square::g8):
                            // white castles king side --> move H rook
                            removeFromBitboards(gameState, Figure::BlackRook, Color::Black, Square::h8);
                            addToBitboards(gameState, Figure::BlackRook, Color::Black, Square::f8);
                            break;

                        case (Square::c8):
                            // white castles queen side --> move A rook
                            removeFromBitboards(gameState, Figure::BlackRook, Color::Black, Square::a8);
                            addToBitboards(gameState, Figure::BlackRook, Color::Black, Square::d8);
                            break;
                        default:
                            // TODO throw exception
                            break;
                    }
                }

                // make sure that king has not been exposed into a check
                if (const Square kingsSquare = BitBoardOperations::bitScanForward(gameState.board.bitboards[Figure::BlackKing]);
                        AttackQueries::squareIsAttackedByWhite(gameState.board, kingsSquare))
                {
                    // take move back
                    gameState.board = boardCopy;

                    // return illegal move
                    return false;
                }

                // update castling rights
                gameState.board.castlingRights = updateCastlingRights(gameState.board.castlingRights, sourceSquare, targetSquare);
                // change side to move
                gameState.board.sideToMove = Color::White;

                // return legal move
                return true;
            }

            // Neither MoveType::AllMoves nor capture move --> won't be executed
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

        static void handlePawnPromotion(GameState &gameState, Move move, Figure pawn, Color color, Square targetSquare)
        {
            if (const Figure promotedPiece = move.getPromotedPiece();
                    promotedPiece != Figure::None)
            {
                // erase the pawn from the target square
                removeFromBitboards(gameState, pawn, color, targetSquare);
                // set up promoted movedFigure on chess board
                addToBitboards(gameState, promotedPiece, color, targetSquare);
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