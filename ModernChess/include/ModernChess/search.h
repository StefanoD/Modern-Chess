#pragma once

#include <cinttypes>

/*********************************************************************
*                              CPW-engine                            *
*           created by some members of Chessprogramming Wiki         *
*                                                                    *
* search.h  -  this file names functions coded within search.cpp.    *
* Outside that file they are represented by the interface function   *
* called search_run().                                               *
*********************************************************************/

void search_iterate();
int search_widen(int depth, int val);
void search_clearDriver();
int search_root(uint8_t depth, int alpha, int beta);
int Search(uint8_t depth, uint8_t ply, int alpha, int beta, int can_null, int is_pv);
void setKillers(smove m, uint8_t ply);
void ReorderMoves(smove * m, uint8_t mcount, uint8_t ply);
int info_currmove(smove m, int nr);
int info_pv(int val);
unsigned int countNps(unsigned int nodes, unsigned int time);
void ageHistoryTable();
int contempt();