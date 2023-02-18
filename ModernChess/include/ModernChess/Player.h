#pragma once

#include "BitBoard.h"
#include "Color.h"

namespace ModernChess
{
    class Player
    {
    public:

        BitBoard board{};
        bool onTurn{};
        Color color = Color::Undefined;
    };
}