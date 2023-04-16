#pragma once

#include "BitBoardConstants.h"
#include "Color.h"
#include <ostream>

namespace ModernChess {
    class BitBoard;
}

std::ostream& print(std::ostream& os, ModernChess::BitBoardState bitBoardState);

std::ostream& printAttackedSquares(std::ostream& os, const ModernChess::BitBoard &board, ModernChess::Color attacker);