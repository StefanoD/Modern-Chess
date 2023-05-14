#pragma once

#include "BitBoardConstants.h"
#include "CastlingRights.h"
#include "Color.h"

#include <array>
#include <ostream>

namespace ModernChess
{
    class Board
    {
    public:
        Board();

        [[nodiscard]] BitBoardState getOccupiedSquares() const;
        [[nodiscard]] BitBoardState getEmptySquares() const;
        [[nodiscard]] BitBoardState getWhiteFigures() const;
        [[nodiscard]] BitBoardState getBlackFigures() const;

        // Every figure-type and every color has its own board representation
        std::array<BitBoardState, 12> bitboards{};
        // Occupancies for white, black and both colors
        std::array<BitBoardState, 3> occupancies{};

        Square enPassantTarget = Square::undefined;
        Color sideToMove = Color::White;
        CastlingRights castlingRights = CastlingRights::Undefined;
    };
}

std::ostream& operator<<(std::ostream& os, const ModernChess::Board &bitBoard);