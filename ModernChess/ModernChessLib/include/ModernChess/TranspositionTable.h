#pragma once

#include "Move.h"

#include <cinttypes>
#include <memory>
#include <functional>

namespace ModernChess {

    ///< @see https://web.archive.org/web/20071031100051/http://www.brucemo.com/compchess/programming/hashing.htm

    enum class HashFlag : uint8_t {
        Exact,
        Alpha,
        Beta
    };

    class TranspositionTable {
    public:
        void resize(size_t mbSize);

    private:
        struct TTEntry {
            uint64_t hash{};
            int32_t score{};
            Move best{};
            uint8_t depth{}; //< current search depth
            HashFlag flag{};
        };

        std::unique_ptr<TTEntry, std::function<void(TTEntry*)>> m_table;
        size_t clusterCount;
    };
}