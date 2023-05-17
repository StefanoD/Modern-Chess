#include "ModernChess/PerftLib/PerformanceTest.h"

#include <iostream>

using namespace ModernChess::Perft;

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

    try
    {
        PerformanceTest performanceTest(fenString);
        performanceTest.executePerformanceTest(depth);
    }
    catch (const std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}