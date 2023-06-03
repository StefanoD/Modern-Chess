#pragma once

#include "PrincipalVariationTable.h"
#include "GameState.h"

#include <array>
#include <limits>
#include <iostream>
#include <memory>

namespace ModernChess
{
    struct EvaluationResult
    {
        explicit EvaluationResult(int32_t score,
                                  uint32_t numberOfNodes,
                                  int32_t depth,
                                  std::unique_ptr<PrincipalVariationTable> pvTable) :
                score(score),
                numberOfNodes(numberOfNodes),
                depth(depth),
                pvTable(std::move(pvTable)){}

        [[nodiscard]] Move bestMove() const { return *pvTable->begin(); }
        int32_t score{};
        uint32_t numberOfNodes{};
        uint32_t depth{};
        std::unique_ptr<PrincipalVariationTable> pvTable{};
    };

    class Evaluation
    {
    public:
        explicit Evaluation(GameState gameState) :
            m_gameState{gameState},
            m_halfMoveClockRootSearch{m_gameState.halfMoveClock},
            pvTable{std::make_unique<PrincipalVariationTable>(m_halfMoveClockRootSearch)}
            {
            }

        [[nodiscard]] EvaluationResult getBestMove(int32_t depth);

    protected:
        uint32_t m_numberOfNodes{};
        GameState m_gameState;
        int32_t m_halfMoveClockRootSearch{};
        std::unique_ptr<PrincipalVariationTable> pvTable{};

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

        [[nodiscard]] bool kingIsInCheck() const;

        [[nodiscard]] std::vector<Move> generateSortedMoves() const;

        // negamax alpha beta search
        int32_t negamax(int32_t alpha, int32_t beta, int32_t depth);

        int32_t quiescenceSearch(int32_t alpha, int32_t beta);

        [[nodiscard]] int32_t evaluatePosition() const;

        [[nodiscard]] int32_t scoreMove(Move move) const;

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