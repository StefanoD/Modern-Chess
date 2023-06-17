#include "ModernChess/ZobristHasher.h"
#include "ModernChess/Figure.h"
#include "ModernChess/Square.h"
#include "ModernChess/PseudoRandomGenerator.h"
#include "ModernChess/GameState.h"
#include "ModernChess/BitBoardOperations.h"

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

    uint64_t ZobristHasher::generateHash(const GameState &gameState)
    {
        uint64_t finalKey = 0;

        for (Figure figure = Figure::WhitePawn; figure <= Figure::BlackKing; ++figure)
        {
            for (BitBoardState bitboard = gameState.board.bitboards[figure]; bitboard != BoardState::empty; )
            {
                const Square square = BitBoardOperations::bitScanForward(bitboard);
                finalKey ^= piece_keys[figure][square];

                // pop LS1B
                bitboard = BitBoardOperations::eraseSquare(bitboard, square);
            }
        }

        if (gameState.board.enPassantTarget != Square::undefined)
        {
            finalKey ^= enpassant_keys[gameState.board.enPassantTarget];
        }

        finalKey ^= castle_keys[gameState.board.castlingRights];

        // hash the side only if black is to move
        if (gameState.board.sideToMove == Color::Black)
        {
            finalKey ^= side_key;
        }

        // return generated hash key
        return finalKey;
    }
}