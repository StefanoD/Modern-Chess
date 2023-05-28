#pragma once

#include "BitBoardOperations.h"
#include "PseudoMoveGeneration.h"
#include "MoveExecution.h"
#include "AttackQueries.h"
#include "Figure.h"
#include "Color.h"

#include <array>
#include <limits>

namespace ModernChess
{
    struct EvaluationResult
    {
        explicit EvaluationResult(Move bestMove, int32_t score, uint32_t numberOfNodes) :
                bestMove(bestMove),
                score(score),
                numberOfNodes(numberOfNodes) {}

        Move bestMove{};
        int32_t score{};
        uint32_t numberOfNodes{};
    };

    class Evaluation
    {
    public:
        explicit Evaluation(GameState gameState) :
            m_gameState(gameState),
            m_halfMoveClockRootSearch(m_gameState.halfMoveClock)
            {}

        [[nodiscard]] EvaluationResult getBestMove(uint32_t depth)
        {
            // find best move within a given position
            const int32_t score = negamax(minusInfinity, plusInfinity, depth);

            return EvaluationResult{m_bestMove, score, m_numberOfNodes};
        }

    private:
        uint32_t m_numberOfNodes{};
        Move m_bestMove{};
        GameState m_gameState;
        int32_t m_halfMoveClockRootSearch{};
        // Use here min + 1, otherwise negation of this number won't work
        static constexpr int32_t minusInfinity = std::numeric_limits<int32_t>::min() + 1;
        // Use here min - 1, otherwise negation of this number won't work
        static constexpr int32_t plusInfinity = std::numeric_limits<int32_t>::max() - 1;

        static constexpr int32_t checkMateScore = minusInfinity + 1;
        static constexpr int32_t staleMateScore = 0;

        // negamax alpha beta search
        int32_t negamax(int32_t alpha, int32_t beta, uint32_t depth)
        {
            // recursion escape condition
            if (depth == 0)
            {
                // return evaluation
                return quiescence(alpha, beta);
            }

            // increment nodes count
            ++m_numberOfNodes;

            bool kingInCheck;

            if (m_gameState.board.sideToMove == Color::White)
            {
                const Square kingsSquare = BitBoardOperations::bitScanForward(m_gameState.board.bitboards[Figure::WhiteKing]);
                kingInCheck = AttackQueries::squareIsAttackedByBlack(m_gameState.board, kingsSquare);
            }
            else
            {
                const Square kingsSquare = BitBoardOperations::bitScanForward(m_gameState.board.bitboards[Figure::BlackKing]);
                kingInCheck = AttackQueries::squareIsAttackedByWhite(m_gameState.board, kingsSquare);
            }

            // legal moves counter
            uint32_t legalMoves = 0;

            // best move so far
            Move bestMoveSoFar;

            // old value of alpha
            const int32_t oldAlpha = alpha;

            // create move list instance
            const std::vector<Move> moves = PseudoMoveGeneration::generateMoves(m_gameState);

            // loop over moves within a move list
            for (const Move move : moves)
            {
                // preserve board state
                const GameState gameStateCopy = m_gameState;

                // make sure to make only legal moves
                if (not MoveExecution::executeMove(m_gameState, move, MoveType::AllMoves))
                {
                    // skip to next move
                    continue;
                }

                ++legalMoves;

                // score current move
                const int32_t score = -negamax(-beta, -alpha, depth - 1);

                // take move back
                m_gameState = gameStateCopy;

                // fail-hard beta cutoff
                if (score >= beta)
                {
                    // node (move) fails high
                    return beta;
                }

                // found a better move
                if (score > alpha)
                {
                    // PV node (move)
                    alpha = score;

                    // if root move
                    if (m_gameState.halfMoveClock == m_halfMoveClockRootSearch)
                    {
                        // associate best move with the best score
                        bestMoveSoFar = move;
                    }
                }
            }

            // we don't have any legal moves to make in the current position
            if (legalMoves == 0)
            {
                // king is in check
                if (kingInCheck)
                {    // return mating score (assuming closest distance to mating position)
                    return checkMateScore + m_gameState.halfMoveClock;
                }
                // king is not in check
                // return stalemate score
                return staleMateScore;
            }

            // found better move
            if (oldAlpha != alpha)
            {
                // init best move
                m_bestMove = bestMoveSoFar;
            }

            // node (move) fails low
            return alpha;
        }

        // quiescence search
        int32_t quiescence(int32_t alpha, int32_t beta)
        {
            // evaluate position
            const int32_t evaluation = evaluatePosition();

            // fail-hard beta cutoff
            if (evaluation >= beta)
            {
                // node (move) fails high
                return beta;
            }

            // found a better move
            if (evaluation > alpha)
            {
                // PV node (move)
                alpha = evaluation;
            }

            const std::vector<Move> moves = PseudoMoveGeneration::generateMoves(m_gameState);

            // loop over moves within a move list
            for (const Move move : moves)
            {
                // preserve board state
                const GameState gameStateCopy = m_gameState;

                // make sure to make only legal moves
                if (not MoveExecution::executeMove(m_gameState, move, MoveType::CapturesOnly))
                {
                    // skip to next move
                    continue;
                }

                // score current move
                const int32_t score = -quiescence(-beta, -alpha);

                // take move back
                m_gameState = gameStateCopy;

                // fail-hard beta cutoff
                if (score >= beta)
                {
                    // node (move) fails high
                    return beta;
                }

                // found a better move
                if (score > alpha)
                {
                    // PV node (move)
                    alpha = score;
                }
            }

            // node (move) fails low
            return alpha;
        }

        int32_t evaluatePosition()
        {
            // static evaluation score
            int32_t score = 0;

            // loop over piece bitboards
            for (Figure figure = Figure::WhitePawn; figure <= Figure::BlackKing; ++figure)
            {
                // loop over figure within a bitboard

                for (BitBoardState bitboard = m_gameState.board.bitboards[figure]; bitboard != BoardState::empty; )
                {
                    const Square square = BitBoardOperations::bitScanForward(bitboard);

                    // score material weights
                    score += materialScore[figure];

                    // score positional piece scores
                    switch (figure)
                    {
                        // evaluate white pieces
                        case Figure::WhitePawn: score += pawnScore[square]; break;
                        case Figure::WhiteKnight: score += knightScore[square]; break;
                        case Figure::WhiteBishop: score += bishopScore[square]; break;
                        case Figure::WhiteRook: score += rookScore[square]; break;
                        case Figure::WhiteKing: score += kingScore[square]; break;

                        // evaluate black pieces
                        case Figure::BlackPawn: score -= pawnScore[mirrorScore[square]]; break;
                        case Figure::BlackKnight: score -= knightScore[mirrorScore[square]]; break;
                        case Figure::BlackBishop: score -= bishopScore[mirrorScore[square]]; break;
                        case Figure::BlackRook: score -= rookScore[mirrorScore[square]]; break;
                        case Figure::BlackKing: score -= kingScore[mirrorScore[square]]; break;
                        default:
                            // TODO queen
                            break;
                    }

                    // pop ls1b
                    bitboard = BitBoardOperations::eraseSquare(bitboard, square);
                }
            }

            // return final evaluation based on side
            return (m_gameState.board.sideToMove == Color::White) ? score : -score;
        }

        /*
         *   Material Score
         *
         *   ♙ =   100   = ♙
         *   ♘ =   300   = ♙ * 3
         *   ♗ =   350   = ♙ * 3 + ♙ * 0.5
         *   ♖ =   500   = ♙ * 5
         *   ♕ =   1000  = ♙ * 10
         *   ♔ =   10000 = ♙ * 100
         */

        static constexpr std::array<int32_t, 12> materialScore {
            100,      // white pawn score
            300,      // white knight score
            350,      // white bishop score
            500,      // white rook score
            1000,      // white queen score
            10000,      // white king score
            -100,      // black pawn score
            -300,      // black knight score
            -350,      // black bishop score
            -500,      // black rook score
            -1000,      // black queen score
            -10000,      // black king score
        };

        // pawn positional score
        static constexpr std::array<int32_t, 64> pawnScore =
        {
            0,   0,   0,   0,   0,   0,   0,   0,
            0,   0,   0, -10, -10,   0,   0,   0,
            0,   0,   0,   5,   5,   0,   0,   0,
            5,   5,  10,  20,  20,   5,   5,   5,
            10,  10,  10,  20,  20,  10,  10,  10,
            20,  20,  20,  30,  30,  30,  20,  20,
            30,  30,  30,  40,  40,  30,  30,  30,
            90,  90,  90,  90,  90,  90,  90,  90,
        };

        // knight positional score
        static constexpr std::array<int32_t, 64> knightScore =
        {
            -5, -10,   0,   0,   0,   0, -10,  -5,
            -5,   0,   0,   0,   0,   0,   0,  -5,
            -5,   5,  20,  10,  10,  20,   5,  -5,
            -5,  10,  20,  30,  30,  20,  10,  -5,
            -5,  10,  20,  30,  30,  20,  10,  -5,
            -5,   5,  20,  20,  20,  20,   5,  -5,
            -5,   0,   0,  10,  10,   0,   0,  -5,
            -5,   0,   0,   0,   0,   0,   0,  -5,
        };

        // bishop positional score
        static constexpr std::array<int32_t, 64> bishopScore =
        {
            0,   0, -10,   0,   0, -10,   0,   0,
            0,  30,   0,   0,   0,   0,  30,   0,
            0,  10,   0,   0,   0,   0,  10,   0,
            0,   0,  10,  20,  20,  10,   0,   0,
            0,   0,  10,  20,  20,  10,   0,   0,
            0,   0,   0,  10,  10,   0,   0,   0,
            0,   0,   0,   0,   0,   0,   0,   0,
            0,   0,   0,   0,   0,   0,   0,   0,

        };

        // rook positional score
        static constexpr std::array<int32_t, 64> rookScore =
        {
             0,   0,   0,  20,  20,   0,   0,   0,
             0,   0,  10,  20,  20,  10,   0,   0,
             0,   0,  10,  20,  20,  10,   0,   0,
             0,   0,  10,  20,  20,  10,   0,   0,
             0,   0,  10,  20,  20,  10,   0,   0,
             0,   0,  10,  20,  20,  10,   0,   0,
            50,  50,  50,  50,  50,  50,  50,  50,
            50,  50,  50,  50,  50,  50,  50,  50,
        };

        // king positional score
        static constexpr std::array<int32_t, 64> kingScore =
        {
            0,   0,   5,   0, -15,   0,  10,   0,
            0,   5,   5,  -5,  -5,   0,   5,   0,
            0,   0,   5,  10,  10,   5,   0,   0,
            0,   5,  10,  20,  20,  10,   5,   0,
            0,   5,  10,  20,  20,  10,   5,   0,
            0,   5,   5,  10,  10,   5,   5,   0,
            0,   0,   5,   5,   5,   5,   0,   0,
            0,   0,   0,   0,   0,   0,   0,   0,
        };

        // mirror positional score tables for opposite side
        static constexpr std::array<Square, 64> mirrorScore =
        {
            a8, b8, c8, d8, e8, f8, g8, h8,
            a7, b7, c7, d7, e7, f7, g7, h7,
            a6, b6, c6, d6, e6, f6, g6, h6,
            a5, b5, c5, d5, e5, f5, g5, h5,
            a4, b4, c4, d4, e4, f4, g4, h4,
            a3, b3, c3, d3, e3, f3, g3, h3,
            a2, b2, c2, d2, e2, f2, g2, h2,
            a1, b1, c1, d1, e1, f1, g1, h1,
        };
    };
}