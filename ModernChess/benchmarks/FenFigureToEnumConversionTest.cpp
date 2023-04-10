#include "ModernChess/FlatMap.h"
#include "ModernChess/Figure.h"

#include <benchmark/benchmark.h>

#include <string>

using namespace ModernChess;

namespace {

    enum FenEnums : uint8_t
    {
        P = 'P',
        N = 'N',
        B = 'B',
        R = 'R',
        Q = 'Q',
        K = 'K',
        p = 'p',
        n = 'n',
        b = 'b',
        r = 'r',
        q = 'q',
        k = 'k'
    };

    constexpr FlatMap<uint8_t, FenEnums, 12> fenToEnum {
            {{
                     {'P', P},
                     {'N', N},
                     {'B', B},
                     {'R', R},
                     {'Q', Q},
                     {'K', K},
                     {'p', p},
                     {'n', n},
                     {'b', b},
                     {'r', r},
                     {'q', q},
                     {'k', k}
             }}
    };

    constexpr FenEnums charToEnum(char fenChar)
    {
        switch (fenChar)
        {
            case 'P': return P;
            case 'N': return N;
            case 'B': return B;
            case 'R': return R;
            case 'Q': return Q;
            case 'K': return K;
            case 'p': return p;
            case 'n': return n;
            case 'b': return b;
            case 'r': return r;
            case 'q': return q;
            case 'k': return k;
            default: throw std::range_error("Could not parse FEN character '" + std::string(1, fenChar) + "' to Figure");
        }
    }

    void Enum(benchmark::State &state)
    {
        constexpr std::array<uint8_t, 12> figures{'P', 'p', 'N', 'n', 'B', 'b', 'R', 'r', 'Q', 'q', 'K', 'k'};

        for (auto _: state)
        {
            for (const uint8_t figure: figures)
            {
                const auto value = ColoredFigureType(figure);
                benchmark::DoNotOptimize(value);
            }
        }
    }
    BENCHMARK(Enum);

    void FlatMapToEnum(benchmark::State& state) {
        constexpr std::array<uint8_t, 12> figures{'P', 'p', 'N', 'n', 'B', 'b', 'R', 'r', 'Q', 'q', 'K', 'k'};

        for (auto _ : state)
        {
            for (const uint8_t figure : figures)
            {
                const auto value = fenToEnum.at(figure);
                benchmark::DoNotOptimize(value);
            }
        }
    }
    BENCHMARK(FlatMapToEnum);

    void charToEnumSwitchCase(benchmark::State& state) {
        constexpr std::array<uint8_t, 12> figures{'P', 'p', 'N', 'n', 'B', 'b', 'R', 'r', 'Q', 'q', 'K', 'k'};

        for (auto _ : state)
        {
            for (const uint8_t figure : figures)
            {
                const auto value = charToFigureType(figure);
                benchmark::DoNotOptimize(value);
            }
        }
    }
    BENCHMARK(charToEnumSwitchCase);

    BENCHMARK_MAIN();
}