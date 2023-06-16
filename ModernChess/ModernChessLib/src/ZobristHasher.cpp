#include "ModernChess/ZobristHasher.h"
#include "ModernChess/Figure.h"
#include "ModernChess/Square.h"
#include "ModernChess/PseudoRandomGenerator.h"

namespace ModernChess {

    ZobristHasher::ZobristHasher()
    {
        // loop over piece codes
        for (Figure figure = Figure::WhitePawn; figure <= Figure::BlackKing; ++figure)
        {
            // loop over board squares
            for (Square square = Square::a1; square <= Square::h8; ++square)
            {    // init random figure keys
                piece_keys[figure][square] = PseudoRandomGenerator::getRandomU64Number();
            }
        }

        // loop over board squares
        for (Square square = Square::a1; square <= Square::h8; ++square)
        {    // init random en passant keys
            enpassant_keys[square] = PseudoRandomGenerator::getRandomU64Number();
        }

        // loop over castling keys (see CastlingRights.h)
        for (uint8_t index = 0; index < 16; ++index)
        {
            // init castling keys
            castle_keys[index] = PseudoRandomGenerator::getRandomU64Number();
        }

        // init random side key
        side_key = PseudoRandomGenerator::getRandomU64Number();
    }
}