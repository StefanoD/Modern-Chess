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

    constexpr ColoredFigureType charToFigureType(char fenChar)
    {
        switch (fenChar)
        {
            case 'P': return ColoredFigureType::WhitePawn;
            case 'N': return ColoredFigureType::WhiteKnight;
            case 'B': return ColoredFigureType::WhiteBishop;
            case 'R': return ColoredFigureType::WhiteRook;
            case 'Q': return ColoredFigureType::WhiteQueen;
            case 'K': return ColoredFigureType::WhiteKing;
            case 'p': return ColoredFigureType::BlackPawn;
            case 'n': return ColoredFigureType::BlackKnight;
            case 'b': return ColoredFigureType::BlackBishop;
            case 'r': return ColoredFigureType::BlackRook;
            case 'q': return ColoredFigureType::BlackQueen;
            case 'k': return ColoredFigureType::BlackKing;
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