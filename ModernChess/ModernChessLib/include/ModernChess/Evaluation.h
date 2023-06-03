#pragma once

#include "GlobalConstants.h"
#include "BitBoardOperations.h"
#include "PseudoMoveGeneration.h"
#include "MoveExecution.h"
#include "AttackQueries.h"
#include "Figure.h"
#include "Color.h"

#include <array>
#include <limits>
#include <algorithm>
#include <iostream>

namespace ModernChess
{
    struct EvaluationResult
    {
        explicit EvaluationResult(Move bestMove, int32_t score, uint32_t numberOfNodes, int32_t depth) :
                bestMove(bestMove),
                score(score),
                numberOfNodes(numberOfNodes),
                depth(depth) {}

        Move bestMove{};
        int32_t score{};
        uint32_t numberOfNodes{};
        uint32_t depth{};
    };

    class Evaluation
    {
    public:
        explicit Evaluation(GameState gameState) :
            m_gameState(gameState),
            m_halfMoveClockRootSearch(m_gameState.halfMoveClock)
            {}

        [[nodiscard]] EvaluationResult getBestMove(int32_t depth)
        {
            // find best move within a given position
            const int32_t score = negamax(-infinity, infinity, depth);

            return EvaluationResult{m_bestMove, score, m_numberOfNodes, depth};
        }

    protected:
        uint32_t m_numberOfNodes{};
        Move m_bestMove{};
        GameState m_gameState;
        int32_t m_halfMoveClockRootSearch{};
        // Use half of max number in order to avoid overflows
        static constexpr int32_t infinity = std::numeric_limits<int32_t>::max() / 2;

        static constexpr int32_t checkMateScore = -infinity + 1;
        static constexpr int32_t staleMateScore = 0;
        static constexpr int32_t bestKillerMoveScore = 90'000;
        static constexpr int32_t secondBestKillerMoveScore = 80'000;
        static constexpr int32_t captureScoreOffset = 100'000;
        static constexpr size_t maxNumberOfKillerMoves = 2;

        // killer moves [id][ply]
        std::array<std::array<Move, maxNumberOfKillerMoves>, MaxHalfMoves> killerMoves{};
        // history moves [figure][square]
        std::array<std::array<int32_t, NumberOfFigureTypes>, NumberOfSquares> historyMoves{};

        [[nodiscard]] inline bool kingIsInCheck() const
        {
            if (m_gameState.board.sideToMove == Color::White)
            {
                const Square kingsSquare = BitBoardOperations::bitScanForward(m_gameState.board.bitboards[Figure::WhiteKing]);
                return AttackQueries::squareIsAttackedByBlack(m_gameState.board, kingsSquare);
            }

            const Square kingsSquare = BitBoardOperations::bitScanForward(m_gameState.board.bitboards[Figure::BlackKing]);
            return AttackQueries::squareIsAttackedByWhite(m_gameState.board, kingsSquare);
        }

        [[nodiscard]] inline std::vector<Move> generateSortedMoves() const
        {
            std::vector<Move> moves =  PseudoMoveGeneration::generateMoves(m_gameState);

            // Sort moves, such that captures with higher scores are evaluated first and makes an early pruning more probable
            // Use also stable_sort, because on capture moves, we insert first the most valuable pieces!
            std::stable_sort(moves.begin(), moves.end(), [this](const Move leftOrderedMove, const Move rightOrderedMove){
                return scoreMove(leftOrderedMove) > scoreMove(rightOrderedMove);
            });

            return moves;
        }

        // negamax alpha beta search
        int32_t negamax(int32_t alpha, int32_t beta, int32_t depth)
        {
            const bool kingInCheck = kingIsInCheck();

            // increase search depth if the king has been exposed into a check
            if (kingInCheck)
            {
                ++depth;
            }

            // recursion escape condition
            if (depth == 0)
            {
                // return evaluation
                return quiescenceSearch(alpha, beta);
            }

            // increment nodes count
            ++m_numberOfNodes;

            // legal moves counter
            uint32_t legalMoves = 0;

            // best move so far
            Move bestMoveSoFar;

            // old value of alpha
            const int32_t oldAlpha = alpha;

            // create move list instance
            const std::vector<Move> moves = generateSortedMoves();

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
                    if (not move.isCapture())
                    {
                        // store killer moves for later reuse
                        killerMoves[1][m_gameState.halfMoveClock] = killerMoves[0][m_gameState.halfMoveClock]; // old killer move
                        killerMoves[0][m_gameState.halfMoveClock] = move; // new and better killer move
                    }


                    // node (move) fails high
                    return beta;
                }

                // found a better move
                if (score > alpha)
                {
                    if (not move.isCapture())
                    {
                        // store history moves.
                        // The added value is typically depth * depth or 2 ^ depth,
                        // based on the assumption that otherwise moves from the plies near the leaves would have too
                        // much impact on the result.
                        historyMoves[move.getMovedFigure()][move.getTo()] += (depth * depth);
                    }

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

        int32_t quiescenceSearch(int32_t alpha, int32_t beta)
        {
            ++m_numberOfNodes;

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

            const std::vector<Move> moves = generateSortedMoves();

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
                const int32_t score = -quiescenceSearch(-beta, -alpha);

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

        [[nodiscard]] int32_t evaluatePosition() const
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

        [[nodiscard]] inline int32_t scoreMove(Move move) const
        {
            // score capture move
            if (move.isCapture())
            {
                // init target figure with white pawn or black pawn (doesn't matter which one,
                // because scoring with the same color yields the same valid score), in case of en-passant captures
                Figure targetFigure = Figure::WhitePawn;

                // pick up bitboard figure index ranges depending on side
                Figure opponentsFigureStart;
                Figure opponentsFigureEnd;

                if (m_gameState.board.sideToMove == Color::White)
                {
                    opponentsFigureStart = Figure::BlackPawn;
                    opponentsFigureEnd = Figure::BlackKing;
                }
                else
                {
                    opponentsFigureStart = Figure::WhitePawn;
                    opponentsFigureEnd = Figure::BlackKing;
                }

                for (Figure figure = opponentsFigureStart; figure <= opponentsFigureEnd; ++figure)
                {
                    if (BitBoardOperations::isOccupied(m_gameState.board.bitboards[figure], move.getTo()))
                    {
                        targetFigure = figure;
                        break;
                    }
                }

                // score move by MVV LVA lookup [source piece][target piece]
                return mvvLva[move.getMovedFigure()][targetFigure] + captureScoreOffset;
            }

            // score 1st killer move
            if (killerMoves[0][m_gameState.halfMoveClock] == move)
            {
                return bestKillerMoveScore;
            }

            // score 2nd killer move
            if (killerMoves[1][m_gameState.halfMoveClock] == move)
            {
                return secondBestKillerMoveScore;
            }

            return historyMoves[move.getMovedFigure()][move.getTo()];
        }


        /*
         * @see https://www.chessprogramming.org/MVV-LVA
         *
         *   (Victims) Pawn Knight Bishop   Rook  Queen   King
         *
         * (Attackers)
         *       Pawn   105    205    305    405    505    605
         *     Knight   104    204    304    404    504    604
         *     Bishop   103    203    303    403    503    603
         *       Rook   102    202    302    402    502    602
         *      Queen   101    201    301    401    501    601
         *       King   100    200    300    400    500    600
         */

        // most valuable victim & less valuable attacker [attacker][victim]
        static constexpr std::array<std::array<int32_t, NumberOfFigureTypes>, NumberOfFigureTypes> mvvLva {
            {
                {105, 205, 305, 405, 505, 605,  105, 205, 305, 405, 505, 605},
                {104, 204, 304, 404, 504, 604,  104, 204, 304, 404, 504, 604},
                {103, 203, 303, 403, 503, 603,  103, 203, 303, 403, 503, 603},
                {102, 202, 302, 402, 502, 602,  102, 202, 302, 402, 502, 602},
                {101, 201, 301, 401, 501, 601,  101, 201, 301, 401, 501, 601},
                {100, 200, 300, 400, 500, 600,  100, 200, 300, 400, 500, 600},

                {105, 205, 305, 405, 505, 605,  105, 205, 305, 405, 505, 605},
                {104, 204, 304, 404, 504, 604,  104, 204, 304, 404, 504, 604},
                {103, 203, 303, 403, 503, 603,  103, 203, 303, 403, 503, 603},
                {102, 202, 302, 402, 502, 602,  102, 202, 302, 402, 502, 602},
                {101, 201, 301, 401, 501, 601,  101, 201, 301, 401, 501, 601},
                {100, 200, 300, 400, 500, 600,  100, 200, 300, 400, 500, 600}
            }
        };

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

        static constexpr std::array<int32_t, NumberOfFigureTypes> materialScore {
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
        static constexpr std::array<int32_t, NumberOfSquares> pawnScore =
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
        static constexpr std::array<int32_t, NumberOfSquares> knightScore =
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
        static constexpr std::array<int32_t, NumberOfSquares> bishopScore =
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
        static constexpr std::array<int32_t, NumberOfSquares> rookScore =
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
        static constexpr std::array<int32_t, NumberOfSquares> kingScore =
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
        static constexpr std::array<Square, NumberOfSquares> mirrorScore =
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

std::ostream &operator<<(std::ostream &os, const ModernChess::EvaluationResult &evalResult);