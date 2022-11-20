
#include "ModernChess/stdafx.h"
#include "ModernChess/0x88_math.h"


int isAttacked( char byColor, int8_t sq ) {

    /* pawns */
    if ( byColor == WHITE && b.pawn_ctrl[WHITE][sq] )
         return 1;
    
	if ( byColor == BLACK && b.pawn_ctrl[BLACK][sq])
		 return 1;

    /* knights */
    if ( leaperAttack( byColor, sq, KNIGHT ) )
        return 1;

    /* kings */
    if ( leaperAttack( byColor, sq, KING ) )
        return 1;

    /* straight line sliders */
    if ( straightAttack( byColor, sq, NORTH ) 
	||   straightAttack( byColor, sq, SOUTH ) 
	||   straightAttack( byColor, sq, EAST  ) 
	||   straightAttack( byColor, sq, WEST  ) )
         return 1;

    /* diagonal sliders */
    if ( diagAttack( byColor, sq, NE ) 
	||   diagAttack( byColor, sq, SE ) 
	||   diagAttack( byColor, sq, NW ) 
	||   diagAttack( byColor, sq, SW ) )
         return 1;

    return 0;
}

int leaperAttack( char byColor, int8_t sq, char byPiece ) {
    int8_t nextSq;
    for ( int dir = 0; dir < 8; dir++ ) {
        nextSq = sq + vector[byPiece][dir];
        if ( IS_SQ(nextSq) 
		&&  isPiece( byColor, byPiece, nextSq ) )
            return 1;
    }
    return 0;
}


int straightAttack(char byColor, int8_t sq, int vect) {
    int nextSq = sq + vect;

    while ( IS_SQ(nextSq) ) {
        if (b.color[nextSq] != COLOR_EMPTY ) {
            if ( ( b.color[nextSq] == byColor ) 
			&&   ( b.pieces[nextSq] == ROOK || b.pieces[nextSq] == QUEEN ) )
               return 1;
            return 0;
        }
        nextSq = nextSq + vect;
    }
    return 0;
}


int diagAttack(int byColor, int8_t sq, int vect) {
    int nextSq = sq + vect;

    while ( IS_SQ( nextSq ) ) {
        if (b.color[ nextSq ] != COLOR_EMPTY ) {
            if ( ( b.color[nextSq] == byColor ) 
			&&   ( b.pieces[nextSq] == BISHOP || b.pieces[nextSq] == QUEEN ) )
               return 1;
            return 0;
        }
        nextSq = nextSq + vect;
    }
    return 0;
}

int bishAttack(int byColor, int8_t sq, int vect) {
	int nextSq = sq + vect;

	while (IS_SQ(nextSq)) {
		if (b.color[nextSq] != COLOR_EMPTY) {
			if (b.color[nextSq] == byColor
			&&  b.pieces[nextSq] == BISHOP)
				return 1;
			return 0;
		}
		nextSq = nextSq + vect;
	}
	return 0;
}