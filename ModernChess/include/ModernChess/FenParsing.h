#pragma once

#include "Figure.h"
#include "GameState.h"

#include <array>
#include <string_view>
#include <string>

namespace ModernChess::FenParsing {
    // See https://de.wikipedia.org/wiki/Forsyth-Edwards-Notation

    // ASCII pieces
    constexpr auto asciiFigures = "PNBRQKpnbrqk";

    // unicode pieces
    constexpr std::array<std::string_view, 12> unicodeFigures {"♟︎", "♞", "♝", "♜", "♛", "♚", "♙", "♘", "♗", "♖", "♕", "♔"};

    constexpr FigureType charToFigureType(char fenChar)
    {
        switch (fenChar)
        {
            case 'P': return FigureType::WhitePawn;
            case 'N': return FigureType::WhiteKnight;
            case 'B': return FigureType::WhiteBishop;
            case 'R': return FigureType::WhiteRook;
            case 'Q': return FigureType::WhiteQueen;
            case 'K': return FigureType::WhiteKing;
            case 'p': return FigureType::BlackPawn;
            case 'n': return FigureType::BlackKnight;
            case 'b': return FigureType::BlackBishop;
            case 'r': return FigureType::BlackRook;
            case 'q': return FigureType::BlackQueen;
            case 'k': return FigureType::BlackKing;
            default: throw std::range_error("Could not parse FEN character '" + std::string(1, fenChar) + "' to Figure");
        }
    }

    constexpr auto startPosition = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

    class FenParser
    {
    public:
        GameState parse(std::string_view fen);

    private:
        std::string_view::iterator beginPos{};
        std::string_view::iterator currentPos{};
        std::string_view::iterator endPos{};

        [[nodiscard]] std::string getCurrentPosition() const;

        bool isRankNumber(char character) const;

        void nextPosition();

        char getNextCharacter();

        bool hasNextCharacter();

        Color parseColor(char character) const;

        Square parseSquare();

        uint32_t parseNumber();

        void parseCastlingRights(GameState &gameState);

        static void initOccupancyMaps(GameState &gameState);
    };


}