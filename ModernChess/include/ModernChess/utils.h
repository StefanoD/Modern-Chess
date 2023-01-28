#pragma once

#include "smove.h"

int util_pv(char * pv);
void perft_start(char * command);
void util_bench(char * command);
smove strToMove(char * a);
int algebraic_moves(char * a);
char * algebraic_writemove(smove m, char * a);
void convert_0x88_a(uint8_t sq, char * a);
uint8_t convert_a_0x88(char * a) ;