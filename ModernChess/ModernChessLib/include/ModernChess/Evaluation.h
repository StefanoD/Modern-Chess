#pragma once

#include "BitBoardOperations.h"
#include "PseudoMoveGeneration.h"
#include "MoveExecution.h"
#include "Figure.h"
#include "Color.h"

#include <array>

namespace ModernChess
{
    class Evaluation
    {
    public:
        explicit Evaluation(GameState &gameState) : m_gameState(gameState) {}

        void searchPosition(uint32_t depth)
        {
            std::ignore = depth;
        }

        // negamax alpha beta search
        int32_t negamax(int32_t alpha, int32_t beta, uint32_t depth)
        {
            // recursion escape condition
            if (depth == 0)
            {
                // return evaluation
                return evaluatePosition(m_gameState.board.sideToMove, m_gameState.board.bitboards);
            }

            // increment nodes count
            ++m_numberOfNodes;

            // best move so far
            Move bestSoFar;

            // old value of alpha
            const int32_t oldAlpha = alpha;

            // create move list instance
            const std::vector<Move> moves = PseudoMoveGeneration::generateMoves(m_gameState);

            // loop over moves within a move list
            for (const Move move : moves)
            {
                // preserve board state
                const Board boardCopy = m_gameState.board;

                ++m_gameState.halfMoveClock;

                // make sure to make only legal moves
                if (not MoveExecution::executeMove(m_gameState, move, MoveType::AllMoves))
                {
                    // decrement ply
                    --m_gameState.halfMoveClock;

                    // skip to next move
                    continue;
                }

                // score current move
                const int32_t score = -negamax(-beta, -alpha, depth - 1);

                // decrement ply
                --m_gameState.halfMoveClock;

                // take move back
                m_gameState.board = boardCopy;

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
                    if (m_gameState.halfMoveClock == 0)
                    {
                        // associate best move with the best score
                        bestSoFar = move;
                    }
                }
            }

            // found better move
            if (oldAlpha != alpha)
            {
                // init best move
                m_bestMove = bestSoFar;
            }

            // node (move) fails low
            return alpha;
        }

        static inline int32_t evaluatePosition(Color sideToPlay, const std::array<BitBoardState, 12> &bitboards)
        {
            // static evaluation score
            int32_t score = 0;

            // loop over piece bitboards
            for (Figure figure = Figure::WhitePawn; figure <= Figure::BlackKing; ++figure)
            {
                // loop over figure within a bitboard

                for (BitBoardState bitboard = bitboards[figure]; bitboard != BoardState::empty; )
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
            return (sideToPlay == Color::White) ? score : -score;
        }

    private:
        uint32_t m_numberOfNodes{};
        Move m_bestMove{};
        GameState &m_gameState;

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