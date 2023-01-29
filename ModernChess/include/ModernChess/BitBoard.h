#pragma once

#include <bitset>
#include <bit>
#include <string>

namespace ModernChess
{
    constexpr int numberSquares = 64;
    using BitBoardState = std::bitset<numberSquares>;

    // TODO Square-centric representation \
    //  - function to map FEN notation to board state
    //  - function to map from geometric to bitmap

    // TODO function to bitwise and all bitmaps -> Piece captures (different colors), illegal moves (same colors) etc.
    class BitBoard
    {
    public:

        BitBoard();

        [[nodiscard]] BitBoardState getOccupiedSquares() const;
        [[nodiscard]] BitBoardState getEmptySquares() const;
        [[nodiscard]] BitBoardState getWhiteFigures() const;
        [[nodiscard]] BitBoardState getBlackFigures() const;

        [[nodiscard]] static std::string printBitBoard(const BitBoardState &bitBoard);

        // Every piece-type and every color has its own board representation
        BitBoardState blackRookBitBoard;
        BitBoardState blackKnightBitBoard;
        BitBoardState blackBishopBitBoard;
        BitBoardState blackQueenBitBoard;
        BitBoardState blackKingBitBoard;
        BitBoardState blackPawnBitBoard;

        BitBoardState whiteRookBitBoard;
        BitBoardState whiteKnightBitBoard;
        BitBoardState whiteBishopBitBoard;
        BitBoardState whiteQueenBitBoard;
        BitBoardState whiteKingBitBoard;
        BitBoardState whitePawnBitBoard;
    };


}