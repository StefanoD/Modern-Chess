#pragma once

#include "BitBoardConstants.h"
#include <ostream>

namespace ModernChess
{
    std::ostream& print(std::ostream& os, const ModernChess::BitBoardState bitBoardState);
}
