#pragma once

#include <cinttypes>

namespace ModernChess {
    // Constants from https://www.chessprogramming.org/Square_Mapping_Considerations
    // We use Little-Endian Rank-File Mapping

    using BitBoardState = uint64_t;

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