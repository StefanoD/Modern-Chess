#pragma once

#pragma once

#include "Figure.h"
#include "FlatMap.h"

namespace ModernChess {

    // TODO Optimize to use array designators in C++ somehow
    constexpr FlatMap<char, ColoredFigureTypes, 12> fenToEnum {
            {{
                     {'P', WhitePawn},
                     {'N', WhiteKnight},
                     {'B', WhiteBishop},
                     {'R', WhiteRook},
                     {'Q', WhiteQueen},
                     {'K', WhiteKing},
                     {'p', BlackPawn},
                     {'n', BlackKnight},
                     {'b', BlackBishop},
                     {'r', BlackRook},
                     {'q', BlackQueen},
                     {'k', BlackKing}
             }}
    };
}