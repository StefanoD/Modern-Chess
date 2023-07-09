#pragma once
#include "ModernChess/MoveExecution.h"
#include "ModernChess/PseudoMoveGeneration.h"
#include "ModernChess/FenParsing.h"

#include <vector>
#include <iostream>
#include <chrono>
#include <string_view>

using namespace ModernChess;
using namespace ModernChess::MoveGenerations;

namespace ModernChess::Perft {

    class PerformanceTest {
    public:
        explicit PerformanceTest(std::string_view fenString)
        {
            FenParsing::FenParser fenParser(fenString);
            m_gameState = fenParser.parse();

            std::cout << m_gameState << std::endl;
        }

        uint64_t executePerformanceTest(int depth)
        {
            std::cout << "\n     Performance test\n\n";

            // create move list instance
            std::vector<Move> moveList;
            moveList.reserve(256);

            auto begin = std::chrono::high_resolution_clock::now();

            // generate moves
            generateMoves(moveList);

            uint64_t accumulatedNodes = 0;

            // loop over generated moves
            for (const Move move : moveList)
            {
                // preserve board state
                const GameState gameStateCopy = m_gameState;

                // make move
                if (const bool kingIsNotInCheck = makeMove(move, MoveType::AllMoves);
                        not kingIsNotInCheck)
                {
                    // skip to the next move
                    continue;
                }
                // old nodes
                const uint64_t numberOfNotes = perftDriver(depth - 1);
                accumulatedNodes += numberOfNotes;
                // take back
                m_gameState = gameStateCopy;

                const uint64_t hashFromScratch = ZobristHasher::generateHash(m_gameState);

                if (m_gameState.gameStateHash != hashFromScratch)
                {
                    std::cout << "Hash should be " << hashFromScratch << " after take-back, but it is " << m_gameState.gameStateHash << std::endl;
                    std::cout << "Move: " << move << std::endl;
                    std::cout << m_gameState.gameStateHash << std::endl;
                }

                // print move
                //std::cout << move << "\t nodes: " << numberOfNotes << std::endl;
            }

            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

            // print results
            std::cout << "\n    Depth: " << depth << std::endl;
            std::cout << "    Nodes: " << accumulatedNodes << std::endl;
            std::cout << "Elapsed time: " << elapsed << " ms" << std::endl;

            return accumulatedNodes;
        }

    private:
        GameState m_gameState;

        bool makeMove(Move move, MoveType moveType)
        {
            if (m_gameState.board.sideToMove == Color::White)
            {
                return MoveExecution::executeMoveForWhite(m_gameState, move, moveType);
            }

            return MoveExecution::executeMoveForBlack(m_gameState, move, moveType);
        }

        void generateMoves(std::vector<Move> &movesToBeGenerated)
        {
            if (m_gameState.board.sideToMove == Color::White)
            {
                PseudoMoveGeneration::generateWhiteFigureMoves(m_gameState, movesToBeGenerated);
            }
            else
            {
                PseudoMoveGeneration::generateBlackFigureMoves(m_gameState, movesToBeGenerated);
            }
        }

        uint64_t perftDriver(int depth)
        {
            uint64_t numberNodes = 0;
            // recursion escape condition
            if (depth == 0)
            {
                // increment numberNodes count (count reached positions)
                ++numberNodes;
                return numberNodes;
            }

            std::vector<Move> move_list;
            move_list.reserve(256);

            generateMoves(move_list);

            for (const Move move : move_list)
            {
                // preserve board state
                const Board boardCopy = m_gameState.board;

                if (const bool kingIsNotInCheck = makeMove(move, MoveType::AllMoves);
                    not kingIsNotInCheck)
                {
                    // skip to the next move
                    continue;
                }

                // call perft driver recursively
                numberNodes += perftDriver(depth - 1);

                // take back
                m_gameState.board = boardCopy;
            }

            return numberNodes;
        }
    };
}
