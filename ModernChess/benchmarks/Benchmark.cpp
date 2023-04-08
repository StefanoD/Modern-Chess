#include "ModernChess/FlatMap.h"
#include "ModernChess/Figure.h"

#include <benchmark/benchmark.h>

using namespace ModernChess;

namespace {

    constexpr int char_pieces[] = {
            ['P'] = WhitePawn,
            ['N'] = WhiteKnight,
            ['B'] = WhiteBishop,
            ['R'] = WhiteRook,
            ['Q'] = WhiteQueen,
            ['K'] = WhiteKing,
            ['p'] = BlackPawn,
            ['n'] = BlackKnight,
            ['b'] = BlackBishop,
            ['r'] = BlackRook,
            ['q'] = BlackQueen,
            ['k'] = BlackKing
    };

    static void ArrayDesignators(benchmark::State &state)
    {
        constexpr std::array<char, 12> figures{'P', 'p', 'N', 'n', 'B', 'b', 'R', 'r', 'Q', 'q', 'K', 'k'};

        for (auto _: state)
        {
            for (char figure: figures)
            {
                const auto value = char_pieces[figure];
                benchmark::DoNotOptimize(value);
            }
        }
    }

    constexpr FlatMap<char, ColoredFigureTypes, 12> fenToEnum {
            {{
                     {'P', WhitePawn},
                     {'N', WhiteKnight},
                     {'B', WhiteBishop},
                     {'R', WhiteRook},
                     {'Q', WhiteQueen},
                     {'K', WhiteKing},
                     {'p', BlackPawn},
                     {'n', BlackKnight},
                     {'b', BlackBishop},
                     {'r', BlackRook},
                     {'q', BlackQueen},
                     {'k', BlackKing}
             }}
    };

    BENCHMARK(ArrayDesignators);


    static void Enum(benchmark::State &state)
    {
        constexpr std::array<char, 12> figures{'P', 'p', 'N', 'n', 'B', 'b', 'R', 'r', 'Q', 'q', 'K', 'k'};

        for (auto _: state)
        {
            for (char figure: figures)
            {
                const auto value = ColoredFigureTypes(figure);
                benchmark::DoNotOptimize(value);
            }
        }
    }

    BENCHMARK(Enum);

    static void FlatMapToEnum(benchmark::State& state) {
        constexpr std::array<char, 12> figures{'P', 'p', 'N', 'n', 'B', 'b', 'R', 'r', 'Q', 'q', 'K', 'k'};

        for (auto _ : state)
        {
            for (char figure : figures)
            {
                const auto value = fenToEnum.at(figure);
                benchmark::DoNotOptimize(value);
            }
        }
    }
    BENCHMARK(FlatMapToEnum);

    BENCHMARK_MAIN();
}