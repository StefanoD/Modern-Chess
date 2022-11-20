#pragma once

/* king safety*/
int wKingShield();
int bKingShield();

/* pawn structure */
int getPawnScore();
int evalPawnStructure();
int EvalPawn(uint8_t sq, int8_t side);
void EvalKnight(uint8_t sq, int8_t side);
void EvalBishop(uint8_t sq, int8_t side);
void EvalRook(uint8_t sq, int8_t side);
void EvalQueen(uint8_t sq, int8_t side);
int isPawnSupported(uint8_t sq, int8_t side);
int isWPSupported(uint8_t sq);
int isBPSupported(uint8_t sq);

/* pattern detection */
void blockedPieces(int side);
