#pragma once

#include "BitBoardConstants.h"
#include "Color.h"
#include "Move.h"

#include <ostream>
#include <vector>

namespace ModernChess {
    class BitBoard;
}

std::ostream& print(std::ostream& os, ModernChess::BitBoardState bitBoardState);

std::ostream& printAttackedSquares(std::ostream& os, const ModernChess::BitBoard &board, ModernChess::Color attacker);

std::ostream &operator<<(std::ostream &os, const std::vector<ModernChess::Move> &moves);