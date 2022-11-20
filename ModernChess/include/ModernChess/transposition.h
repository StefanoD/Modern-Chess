#pragma once

#include "stdafx.h"

struct szobrist {
    uint64_t piecesquare[6][2][128];
    uint64_t color;
    uint64_t castling[16];
    uint64_t ep[128];
} extern zobrist;

enum ettflag {
    TT_EXACT,
    TT_ALPHA,
    TT_BETA
};

struct stt_entry {
    uint64_t  hash;
    int  val;
    uint8_t	 depth;
    uint8_t   flags;
    uint8_t   bestmove;
} extern * tt;

struct spawntt_entry {
    uint64_t  hash;
    int  val;
} extern * ptt;

struct sevaltt_entry {
    uint64_t hash;
    int val;
} extern * ett;

extern uint32_t tt_size;
extern int ptt_size;
extern int ett_size;

uint64_t rand64();
int tt_init();
int tt_setsize(int size);
int tt_probe(uint8_t depth, int alpha, int beta, char * best);
void tt_save(uint8_t depth, int val, char flags, char best);
int ttpawn_setsize(int size);
int ttpawn_probe();
void ttpawn_save(int val);
int tteval_setsize(int size);
int tteval_probe();
void tteval_save(int val);
