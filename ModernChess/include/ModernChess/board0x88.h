#pragma once

#include "stdafx.h"
#include "0x88_math.h"
#include "transposition.h"

void clearBoard();

/******************************************************************************
* fillSq() and clearSq(), beside placing a piece on a given square or erasing *
* it,  must  take care for all the incrementally updated  stuff:  hash  keys, *
* piece counters, material and pcsq values, pawn-related data, king location. *
******************************************************************************/

void fillSq(uint8_t color, uint8_t piece, int8_t sq);


void clearSq(int8_t sq);


int board_loadFromFen(char * fen);


void board_display();