#pragma once

#include <cinttypes>

/*********************************************************************
*                              CPW-engine                            *
*           created by some members of Chessprogramming Wiki         *
*                                                                    *
* movegen.h - this file names functions coded within movegen.cpp.    *
* Only movegen() and movegen_sort() are used outside that file.      *
*********************************************************************/

void movegen_push(char from, char to, uint8_t piece_from, uint8_t piece_cap, char flags);
void movegen_push_qs(char from, char to, uint8_t piece_from, uint8_t piece_cap, char flags);
void movegen_pawn_move(int8_t sq, bool promotion_only);
void movegen_pawn_capt(int8_t sq);