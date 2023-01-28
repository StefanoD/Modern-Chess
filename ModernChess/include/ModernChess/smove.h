#pragma once

#include <cinttypes>

struct smove {
    uint8_t id;
    uint8_t from;
    uint8_t to;
    uint8_t piece_from;
    uint8_t piece_to;
    uint8_t piece_cap;
    char flags;
    uint8_t castle;
    char ply;
    uint8_t ep;
    int score;
};