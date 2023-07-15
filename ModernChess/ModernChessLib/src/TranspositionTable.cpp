#include "ModernChess/TranspositionTable.h"
#include "ModernChess/MemoryAllocator.h"

namespace ModernChess {

    void TranspositionTable::resize(size_t mbSize)
    {
        clusterCount = mbSize * 1024 * 1024 / sizeof(TTEntry);
        m_table = MemoryAllocator::alignedAlloc<TTEntry>(clusterCount * sizeof(TTEntry));
    }
}