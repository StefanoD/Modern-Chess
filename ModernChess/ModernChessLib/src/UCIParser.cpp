#include "ModernChess/UCIParser.h"

#include <cstring>

namespace ModernChess
{
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

    bool UCIParser::uiHasSentStopCommand()
    {
        constexpr auto stopCommand = "stop";

        if (currentStringView().starts_with(stopCommand))
        {
            m_currentPos += strlen(stopCommand);
            return true;
        }
        return false;
    }

    UCIParser::UCIMove UCIParser::parseMove()
    {
        // Uses long algebraic notation, i.e.
        // - "e2e3"
        // - "e7e8q" (promoting to queen)
        const Square sourceSquare = parseSquare();
        const Square targetSquare = parseSquare();

        bool uiSentLegalPromotion = false;

        if (not isAtEndOfString() and
            currentCharacter() != ' ')
        {
            const char promotionCharacter = currentCharacter();

            uiSentLegalPromotion = promotionCharacter == 'q' or
                                   promotionCharacter == 'r' or
                                   promotionCharacter == 'b' or
                                   promotionCharacter == 'n';

            if (not uiSentLegalPromotion)
            {
                // Illegal Move --> Return Null Move
                return UCIMove{Square::undefined, Square::undefined, false};
            }
        }

        // move iterator to next position
        nextPosition();

        return UCIMove{sourceSquare, targetSquare, uiSentLegalPromotion};
    }
}