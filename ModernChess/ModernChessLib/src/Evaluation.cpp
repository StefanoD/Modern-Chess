#include "ModernChess/Evaluation.h"

#include "ModernChess/PseudoMoveGeneration.h"
#include "ModernChess/MoveExecution.h"

#include <algorithm>

std::ostream &operator<<(std::ostream &os, const ModernChess::EvaluationResult &evalResult)
{
    os << "info score cp " << evalResult.score << " depth " << evalResult.depth << " nodes " << evalResult.numberOfNodes << "\n";
    os << "bestmove " << evalResult.bestMove << "\n";

    return os;
}

namespace ModernChess
{
    EvaluationResult Evaluation::getBestMove(int32_t depth)
    {
        // find best move within a given position
        const int32_t score = negamax(-infinity, infinity, depth);

        return EvaluationResult{m_bestMove, score, m_numberOfNodes, depth};
    }

    bool Evaluation::kingIsInCheck() const
    {
        if (m_gameState.board.sideToMove == Color::White)
        {
            const Square kingsSquare = BitBoardOperations::bitScanForward(m_gameState.board.bitboards[Figure::WhiteKing]);
            return AttackQueries::squareIsAttackedByBlack(m_gameState.board, kingsSquare);
        }

        const Square kingsSquare = BitBoardOperations::bitScanForward(m_gameState.board.bitboards[Figure::BlackKing]);
        return AttackQueries::squareIsAttackedByWhite(m_gameState.board, kingsSquare);
    }

    std::vector<Move> Evaluation::generateSortedMoves() const
    {
        std::vector<Move> moves =  PseudoMoveGeneration::generateMoves(m_gameState);

        // Sort moves, such that captures with higher scores are evaluated first and makes an early pruning more probable
        // Use also stable_sort, because on capture moves, we insert first the most valuable pieces!
        std::stable_sort(moves.begin(), moves.end(), [this](const Move leftOrderedMove, const Move rightOrderedMove){
            return scoreMove(leftOrderedMove) > scoreMove(rightOrderedMove);
        });

        return moves;
    }

    int32_t Evaluation::negamax(int32_t alpha, int32_t beta, int32_t depth)
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

    int32_t Evaluation::quiescenceSearch(int32_t alpha, int32_t beta)
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

    int32_t Evaluation::evaluatePosition() const
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
                        // Ignore queen
                        break;
                }

                // pop ls1b
                bitboard = BitBoardOperations::eraseSquare(bitboard, square);
            }
        }

        // return final evaluation based on side
        return (m_gameState.board.sideToMove == Color::White) ? score : -score;
    }

    int32_t Evaluation::scoreMove(Move move) const
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
}