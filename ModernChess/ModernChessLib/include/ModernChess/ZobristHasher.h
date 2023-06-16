#pragma once

#include "GlobalConstants.h"

#include <array>

namespace ModernChess {
    class ZobristHasher {
    public:
        ZobristHasher();

        // random piece keys [piece][square]
        std::array<std::array<uint64_t, NumberOfFigureTypes>, NumberOfSquares> piece_keys;

        // random en passant keys [square]
        std::array<uint64_t, NumberOfSquares> enpassant_keys;

        // random castling keys
        std::array<uint64_t, 16> castle_keys;

        // random side key
        uint64_t side_key;
    };
}