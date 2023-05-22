#include "ModernChess/Move.h"

#include <benchmark/benchmark.h>

#include <vector>

using namespace ModernChess;

namespace {

    void Reserve1024(benchmark::State &state)
    {

        for (auto _: state)
        {
            for (int i = 0; i < 200; ++i)
            {
                std::vector<Move> moves;
                moves.reserve(1024);
                benchmark::DoNotOptimize(moves);
            }
        }
    }
    BENCHMARK(Reserve1024);

    void Reserve512(benchmark::State &state)
    {

        for (auto _: state)
        {
            for (int i = 0; i < 200; ++i)
            {
                std::vector<Move> moves;
                moves.reserve(512);
                benchmark::DoNotOptimize(moves);
            }
        }
    }
    BENCHMARK(Reserve512);

    void Reserve256(benchmark::State &state)
    {

        for (auto _: state)
        {
            for (int i = 0; i < 200; ++i)
            {
                std::vector<Move> moves;
                moves.reserve(256);
                benchmark::DoNotOptimize(moves);
            }
        }
    }
    BENCHMARK(Reserve256);

    void Reserve128(benchmark::State &state)
    {

        for (auto _: state)
        {
            for (int i = 0; i < 200; ++i)
            {
                std::vector<Move> moves;
                moves.reserve(128);
                benchmark::DoNotOptimize(moves);
            }
        }
    }
    BENCHMARK(Reserve128);

    void Reserve64(benchmark::State &state)
    {

        for (auto _: state)
        {
            for (int i = 0; i < 200; ++i)
            {
                std::vector<Move> moves;
                moves.reserve(64);
                benchmark::DoNotOptimize(moves);
            }
        }
    }
    BENCHMARK(Reserve64);

    BENCHMARK_MAIN();
}