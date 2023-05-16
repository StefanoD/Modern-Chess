#include "ModernChess/MoveExecution.h"
#include "ModernChess/PseudoMoveGeneration.h"
#include "ModernChess/FenParsing.h"

#include <vector>
#include <iostream>
#include <chrono>

using namespace ModernChess;
using namespace ModernChess::MoveGenerations;

GameState gameState;

bool makeMove(Move move, MoveType moveType)
{
    if (gameState.board.sideToMove == Color::White)
    {
        return MoveExecution::executeMoveForWhite(gameState, move, moveType);
    }

    return MoveExecution::executeMoveForBlack(gameState, move, moveType);
}

void generateMoves(std::vector<Move> &movesToBeGenerated)
{
    if (gameState.board.sideToMove == Color::White)
    {
        PseudoMoveGeneration::generateWhiteFigureMoves(gameState, movesToBeGenerated);
    }
    else
    {
        PseudoMoveGeneration::generateBlackFigureMoves(gameState, movesToBeGenerated);
    }
}

static inline uint64_t perftDriver(int depth)
{
    uint64_t nodes = 0;
    // recursion escape condition
    if (depth == 0)
    {
        // increment nodes count (count reached positions)
        ++nodes;
        return nodes;
    }

    // create move list instance
    std::vector<Move> move_list;
    move_list.reserve(256);

    // generate moves
    generateMoves(move_list);

    // loop over generated moves
    for (const Move move : move_list)
    {
        // preserve board state
        const Board boardCopy = gameState.board;

        // make move
        if (!makeMove(move, MoveType::AllMoves))
        {    // skip to the next move
            continue;
        }

        // call perft driver recursively
        nodes += perftDriver(depth - 1);

        // take back
        gameState.board = boardCopy;
    }

    return nodes;
}

void perftTest(int depth)
{
    std::cout << "\n     Performance test\n\n";

    // create move list instance
    std::vector<Move> moveList;
    moveList.reserve(256);

    auto begin = std::chrono::high_resolution_clock::now();

    // generate moves
    generateMoves(moveList);

    uint64_t cummulatedNodes = 0;

    // loop over generated moves
    for (const Move move : moveList)
    {
        // preserve board state
        const Board boardCopy = gameState.board;

        // make move
        if (!makeMove(move, MoveType::AllMoves))
            // skip to the next move
            continue;

        // old nodes
        uint64_t oldNodes = perftDriver(depth - 1);
        cummulatedNodes += oldNodes;
        // take back
        gameState.board = boardCopy;

        // print move
        //std::cout << move << "\t nodes: " << oldNodes << std::endl;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

    // print results
    std::cout << "\n    Depth: " << depth << std::endl;
    std::cout << "    Nodes: " << cummulatedNodes << std::endl;
    std::cout << "Elapsed time: " << elapsed << " ms" << std::endl;
}


int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cout << "Pass depth and FEN string as argument. Example:" << std::endl;
        std::cout << "./perft 5 \"r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1\"" << std::endl;
        return 0;
    }

    const int depth = std::stoi(argv[1]);
    const std::string fenString = argv[2];
    FenParsing::FenParser fenParser;
    gameState = fenParser.parse(fenString);
    //gameState = fenParser.parse("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1");

    std::cout << gameState << std::endl;

    try
    {
        perftTest(depth);
    }
    catch (const std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
    }



    return 0;
}