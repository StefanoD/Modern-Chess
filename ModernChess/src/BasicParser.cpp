#include "ModernChess/BasicParser.h"

namespace ModernChess
{
    BasicParser::BasicParser(std::string_view fen) :
            beginPos(fen.begin()),
            currentPos(fen.begin()),
            endPos(fen.end())
    {}

    Square BasicParser::parseSquare()
    {
        char character = *currentPos;
        Square square = Square::undefined;

        if (isAlphabetic(character))
        {
            /**
             *  squareIndex = 8*rankIndex + fileIndex
                FileIndex   = squareIndex modulo 8  = squareIndex & 7
                RankIndex   = squareIndex div    8  = squareIndex >> 3
             */


            // parse en passant file & rank
            const int file = character - 'a';

            character = getNextCharacter();

            if (!isNumerical(character))
            {
                throw std::range_error("Could not parse square from character '" +
                                       std::string(1, character) + "' at position " + getCurrentPosition() +
                                       "! Expected a number!");
            }

            const int rank = character - '1';

            // init en passant square
            square = BitBoardOperations::getSquare(rank, file);
        }
        else if (character == '-')
        {
            // Do nothing
        }
        else
        {
            throw std::range_error("Could not parse square from character '" +
                                   std::string(1, character) + "' at position " + getCurrentPosition() + "!");
        }

        return square;
    }

    std::string BasicParser::getCurrentPosition() const
    {
        return std::to_string(currentPos - beginPos + 1);
    }

    bool BasicParser::isRankNumber(char character) const
    {
        if (character == '9')
        {
            throw std::range_error("Invalid rank number '9' at position " +
                                   getCurrentPosition() + "!");
        }

        return isNumerical(character);
    }

    void BasicParser::nextPosition()
    {
        ++currentPos;
        if (currentPos == endPos)
        {
            const std::string position = getCurrentPosition();
            throw std::range_error("Error at position " + position + ": Unexpected end of line!");
        }
    }

    char BasicParser::getNextCharacter()
    {
        ++currentPos;
        if (currentPos == endPos)
        {
            const std::string position = getCurrentPosition();
            throw std::range_error("Error at position " + position + ": Unexpected end of line!");
        }
        return *currentPos;
    }

    bool BasicParser::hasNextCharacter()
    {
        return (currentPos+1) != endPos;
    }
}


