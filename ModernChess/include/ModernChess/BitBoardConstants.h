#pragma once

#include <cinttypes>

namespace ModernChess {
    // Constants from https://www.chessprogramming.org/Square_Mapping_Considerations
    // We use Little-Endian Rank-File Mapping

    constexpr int numberSquares = 64;
    using BitBoardState = uint64_t;

    enum Square : uint8_t
    {
        a1, b1, c1, d1, e1, f1, g1, h1,
        a2, b2, c2, d2, e2, f2, g2, h2,
        a3, b3, c3, d3, e3, f3, g3, h3,
        a4, b4, c4, d4, e4, f4, g4, h4,
        a5, b5, c5, d5, e5, f5, g5, h5,
        a6, b6, c6, d6, e6, f6, g6, h6,
        a7, b7, c7, d7, e7, f7, g7, h7,
        a8, b8, c8, d8, e8, f8, g8, h8
    };

    enum RayDirections : int
    {
        North = 8,
        NorthEast = 9,
        NorthWest = 7,
        West = -1,
        East = 1,
        SouthWest = -9,
        South = -8,
        SouthEast = -7,
    };

    constexpr BitBoardState aFile = 0x0101010101010101;
    constexpr BitBoardState hFile = 0x8080808080808080;
    constexpr BitBoardState firstRank = 0x00000000000000FF;
    constexpr BitBoardState eightsRank = 0xFF00000000000000;
    constexpr BitBoardState a1H8Diagonal = 0x8040201008040201;
    constexpr BitBoardState h1A8Antidiagonal = 0x0102040810204080;
    constexpr BitBoardState lightSquares = 0x55AA55AA55AA55AA;
    constexpr BitBoardState darkSquares = 0xAA55AA55AA55AA55;
    constexpr BitBoardState notAFile = ~aFile;
    constexpr BitBoardState notHFile = ~hFile;
}