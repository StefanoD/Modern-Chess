#pragma once

#include "ModernChess/FenParsing.h"
#include "ModernChess/Figure.h"
#include "ModernChess/BitBoardOperations.h"

namespace ModernChess::Testing
{
    static Board initBoard()
    {
        Board board = FenParsing::FenParser(FenParsing::startPosition).parse().board;

        return board;
    }
}