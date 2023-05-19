#include "ModernChess/UCIParser.h"

#include <cstring>
#include <algorithm>

namespace ModernChess
{
    static constexpr std::array<Figure, 255> promotionCharacterToPiece = [] {
        std::array<Figure, 255> a{};

        std::fill(a.begin(), a.end(), Figure::None);

        a['n'] = Figure::WhiteKnight;
        a['b'] = Figure::WhiteBishop;
        a['r'] = Figure::WhiteRook;
        a['q'] = Figure::WhiteQueen;
        a['n'] = Figure::BlackKnight;
        a['b'] = Figure::BlackBishop;
        a['r'] = Figure::BlackRook;
        a['q'] = Figure::BlackQueen;
        return a;
    } ();

    UCIParser::UCIParser(std::string_view uiCommand) : BasicParser(uiCommand)
    {}

    bool UCIParser::uiRequestsUCIMode() const
    {
        return currentStringView().starts_with("uci");
    }

    bool UCIParser::uiRequestsNewGame() const
    {
        return currentStringView().starts_with("ucinewgame");
    }

    bool UCIParser::uiIsReady() const
    {
        return currentStringView().starts_with("isready");
    }

    bool UCIParser::uiQuitGame() const
    {
        return currentStringView().starts_with("quit");
    }

    bool UCIParser::uiHasSentPosition()
    {
        constexpr auto positionCommand = "position";

        if (currentStringView().starts_with(positionCommand))
        {
            m_currentPos += strlen(positionCommand);

            // Skip whitespace
            nextPosition();

            return true;
        }
        return false;
    }

    bool UCIParser::uiHasSentMoves()
    {
        constexpr auto movesCommand = "moves";

        if (currentStringView().starts_with(movesCommand))
        {
            m_currentPos += strlen(movesCommand);

            // Skip whitespace
            nextPosition();

            return true;
        }
        return false;
    }

    bool UCIParser::uiHasSentFENPosition()
    {
        constexpr auto fenCommand = "fen";

        if (currentStringView().starts_with(fenCommand))
        {
            m_currentPos += strlen(fenCommand);

            // Skip whitespace
            nextPosition();

            return true;
        }
        return false;
    }

    bool UCIParser::uiHasSentStartingPosition()
    {
        constexpr auto startingPositionCommand = "startpos";

        if (currentStringView().starts_with(startingPositionCommand))
        {
            m_currentPos += strlen(startingPositionCommand);

            // It might have more commands, but maybe not
            if (hasNextCharacter())
            {
                // Skip whitespace
                nextPosition();
            }
            return true;
        }
        return false;
    }

    bool UCIParser::uiHasSentGoCommand()
    {
        constexpr auto goCommand = "go";

        if (currentStringView().starts_with(goCommand))
        {
            m_currentPos += strlen(goCommand);

            // It might have more commands, but maybe not
            if (hasNextCharacter())
            {
                // Skip whitespace
                nextPosition();
            }
            return true;
        }
        return false;
    }

    bool UCIParser::uiHasSentSearchDepth()
    {
        constexpr auto searchDepthCommand = "depth";

        if (currentStringView().starts_with(searchDepthCommand))
        {
            m_currentPos += strlen(searchDepthCommand);

            // Skip whitespace
            nextPosition();

            return true;
        }
        return false;
    }

    Move UCIParser::parseMove()
    {
        // Uses long algebraic notation, i.e.
        // - "e2e3"
        // - "e7e8q" (promoting to queen)
        const Square sourceSquare = parseSquare();
        const Square targetSquare = parseSquare();
        const Figure promotedPiece = promotionCharacterToPiece[currentCharacter()];

        return Move(sourceSquare,
                    targetSquare,
                    Figure::None, // Dummy data
                    promotedPiece,
                    false, // Dummy data
                    false, // Dummy data
                    false, // Dummy data
                    false); // Dummy data
    }
}