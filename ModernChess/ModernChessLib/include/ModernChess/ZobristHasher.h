#pragma once

#include "GlobalConstants.h"

#include <array>

namespace ModernChess {
    class GameState;

    class ZobristHasher {
    public:
        ZobristHasher();

        static uint64_t generateHash(const GameState &gameState);

        // random piece keys [piece][square]
        static std::array<std::array<uint64_t, NumberOfFigureTypes>, NumberOfSquares> piece_keys;

        // random en passant keys [square]
        static std::array<uint64_t, NumberOfSquares> enpassant_keys;

        // random castling keys
        static std::array<uint64_t, 16> castle_keys;

        // random side key
        static uint64_t side_key;
    };
}