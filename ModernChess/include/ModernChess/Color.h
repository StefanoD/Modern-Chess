#pragma once

namespace ModernChess
{
    enum Color : uint8_t
    {
        White = 0,
        Black = 1,
        Any = 2, ///< White or black
        UndefinedColor = 255,
    };
}