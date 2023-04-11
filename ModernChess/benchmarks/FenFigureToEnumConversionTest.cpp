#include "ModernChess/FlatMap.h"

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

    constexpr std::array<FenEnums, 256> simulatedArrayDesignators = [] {
        std::array<FenEnums, 256> a{};
        a['P'] = FenEnums::P;
        a['N'] = FenEnums::N;
        a['B'] = FenEnums::B;
        a['R'] = FenEnums::R;
        a['Q'] = FenEnums::Q;
        a['K'] = FenEnums::K;
        a['p'] = FenEnums::p;
        a['n'] = FenEnums::n;
        a['b'] = FenEnums::b;
        a['r'] = FenEnums::r;
        a['q'] = FenEnums::q;
        a['k'] = FenEnums::k;
        return a;
    } ();

    void Enum(benchmark::State &state)
    {
        constexpr std::array<uint8_t, 12> figures{'P', 'p', 'N', 'n', 'B', 'b', 'R', 'r', 'Q', 'q', 'K', 'k'};

        for (auto _: state)
        {
            for (const uint8_t figure: figures)
            {
                const auto value = FenEnums(figure);
                benchmark::DoNotOptimize(value);
            }
        }
    }
    BENCHMARK(Enum);

    void flatMapToEnum(benchmark::State& state) {
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
    BENCHMARK(flatMapToEnum);

    void charToEnumSwitchCase(benchmark::State& state) {
        constexpr std::array<uint8_t, 12> figures{'P', 'p', 'N', 'n', 'B', 'b', 'R', 'r', 'Q', 'q', 'K', 'k'};

        for (auto _ : state)
        {
            for (const uint8_t figure : figures)
            {
                const auto value = charToEnum(figure);
                benchmark::DoNotOptimize(value);
            }
        }
    }
    BENCHMARK(charToEnumSwitchCase);

    void simulatedArrayDesignatorsBench(benchmark::State& state) {
        constexpr std::array<uint8_t, 12> figures{'P', 'p', 'N', 'n', 'B', 'b', 'R', 'r', 'Q', 'q', 'K', 'k'};

        for (auto _ : state)
        {
            for (const uint8_t figure : figures)
            {
                const auto value = simulatedArrayDesignators[figure];
                benchmark::DoNotOptimize(value);
            }
        }
    }
    BENCHMARK(simulatedArrayDesignatorsBench);

    BENCHMARK_MAIN();
}