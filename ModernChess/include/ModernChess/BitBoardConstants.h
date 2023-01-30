#pragma once

#include <cinttypes>

namespace ModernChess {
    // Constants from https://www.chessprogramming.org/Square_Mapping_Considerations
    // We use Little-Endian Rank-File Mapping

    enum Square
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

    constexpr uint64_t aFile = 0x0101010101010101;
    constexpr uint64_t hFile = 0x8080808080808080;
    constexpr uint64_t firstRank = 0x00000000000000FF;
    constexpr uint64_t eightsRank = 0xFF00000000000000;
    constexpr uint64_t a1H8Diagonal = 0x8040201008040201;
    constexpr uint64_t h1A8Antidiagonal = 0x0102040810204080;
    constexpr uint64_t lightSquares = 0x55AA55AA55AA55AA;
    constexpr uint64_t darkSquares = 0xAA55AA55AA55AA55;
    constexpr uint64_t notAFile = ~aFile;
    constexpr uint64_t notHFile = ~hFile;
}