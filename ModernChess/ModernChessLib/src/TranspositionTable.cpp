#include "ModernChess/TranspositionTable.h"
#include "ModernChess/MemoryAllocator.h"

#include <cstring>

namespace ModernChess {

    TranspositionTable::TranspositionTable()
    {
        resize(4); // Default: 4 MB
    }

    void TranspositionTable::addEntry(uint64_t hash, HashFlag flag, int32_t score, Move best, uint8_t depth)
    {
        const TTEntry entry(hash, flag, score, best, depth);
        const size_t index = hash % m_numberEntries;
        m_table[index] = entry;
    }

    int32_t TranspositionTable::getScore(uint64_t hash, int32_t alpha, int32_t beta, uint8_t depth) const
    {
        const size_t index = hash % m_numberEntries;
        const TTEntry &entry = m_table[index];

        if (entry.hash == hash)
        {
            /* The depth tells how accurate or reasonable a scoring is.
             * I.e. the scoring of 10-ply search is more accurate/reliable than from a 3-ply search.
             */
            if (entry.depth >= depth)
            {
                // PV node score
                if (entry.hashFlag == HashFlag::Exact)
                {
                    return entry.score;
                }
                if (entry.hashFlag == HashFlag::Alpha and entry.score <= alpha)
                {
                    return alpha;
                }
                if (entry.hashFlag == HashFlag::Beta and entry.score >= beta)
                {
                    return beta;
                }
            }
            //RememberBestMove();
        }

        return NoHashEntryFound;
    }

    void TranspositionTable::resize(size_t mbSize)
    {
        m_numberEntries = mbSize * 1024 * 1024 / sizeof(TTEntry);
        m_table = MemoryAllocator::alignedArray<TTEntry>(m_numberEntries * sizeof(TTEntry));
    }

    void TranspositionTable::clear()
    {
        std::memset(m_table.get(), 0, m_numberEntries * sizeof(TTEntry));
    }
}