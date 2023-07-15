#include "ModernChess/TranspositionTable.h"
#include "ModernChess/MemoryAllocator.h"

#include <cstring>

namespace ModernChess {

    TranspositionTable::TranspositionTable()
    {
        resize(4); // Default: 4 MB
    }

    void TranspositionTable::resize(size_t mbSize)
    {
        m_numberEntries = mbSize * 1024 * 1024 / sizeof(TTEntry);
        m_table = MemoryAllocator::alignedAlloc<TTEntry>(m_numberEntries * sizeof(TTEntry));
    }

    void TranspositionTable::clear()
    {
        std::memset(m_table.get(), 0, m_numberEntries * sizeof(TTEntry));
    }
}