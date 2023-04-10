#include "ModernChess/FenParsing.h"
#include "ModernChess/BitBoardOperations.h"

#include <sstream>

using namespace ModernChess;

namespace ModernChess::FenParsing {

    std::string FenParser::getCurrentPosition()
    {
        return std::to_string(currentPos - beginPos + 1);
    }

    bool isAlphabetic(char character)
    {
        return (character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z');
    }

    bool isNumerical(char character)
    {
        return character >= '0' && character <= '9';
    }

    bool FenParser::isRankNumber(char character)
    {
        if (character == '9')
        {
            throw std::range_error("Invalid rank number '9' at position " +
                                   getCurrentPosition() + "!");
        }

        return isNumerical(character);
    }

    void FenParser::nextPosition()
    {
        ++currentPos;
        if (currentPos == endPos)
        {
            const std::string position = getCurrentPosition();
            throw std::range_error("Error at position " + position + ": Unexpected end of line!");
        }
    }

    char FenParser::getNextCharacter()
    {
        ++currentPos;
        if (currentPos == endPos)
        {
            const std::string position = getCurrentPosition();
            throw std::range_error("Error at position " + position + ": Unexpected end of line!");
        }
        return *currentPos;
    }

    bool FenParser::hasNextCharacter()
    {
        return (currentPos+1) != endPos;
    }

    Color FenParser::parseColor(char character)
    {
        Color color;

        if (character == 'w')
        {
            color = Color::White;
        }
        else if (character == 'b')
        {
            color = Color::Black;
        }
        else
        {
            throw std::range_error("Expected 'w' or 'b' for color, but got '" + std::string(1, character) +
                                   "' at position " + getCurrentPosition() + "!");
        }

        return color;
    }

    Square FenParser::parseSquare()
    {
        char character = *currentPos;
        Square square = Square::undefined;

        if (isAlphabetic(character))
        {
            // parse en passant file & rank
            const int file = character - 'a';

            character = getNextCharacter();

            if (!isNumerical(character))
            {
                throw std::range_error("Could not parse square from character '" +
                                       std::string(1, character) + "' at position " + getCurrentPosition() +
                                       "! Expected a number!");
            }

            const int rank = 8 - (character - '0');

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

    uint32_t FenParser::parseNumber()
    {
        std::stringstream strNumber;

        for (char character = getNextCharacter();
             isNumerical(character);
             character = getNextCharacter())
        {
            strNumber << character;

            if (!hasNextCharacter())
            {
                break;
            }
        }

        uint32_t number = 0;
        strNumber >> number;

        if (strNumber.fail())
        {
            throw std::range_error("Could not parse number \"" + strNumber.str() +
                                   "\" at position " + getCurrentPosition() + "!");
        }

        // The last character was not a number. Therefore, decrement position again
        --currentPos;

        return number;
    }

    void FenParser::parseCastlingRights(GameState &gameState)
    {
        char character = getNextCharacter();

        // parse castling rights
        while (character != ' ')
        {
            switch (character)
            {
                case 'K': gameState.castleRights = addWhiteKingSideCastleRights(gameState.castleRights); break;
                case 'Q': gameState.castleRights = addWhiteQueenSideCastleRights(gameState.castleRights); break;
                case 'k': gameState.castleRights = addBlackKingSideCastleRights(gameState.castleRights); break;
                case 'q': gameState.castleRights = addBlackQueenSideCastleRights(gameState.castleRights); break;
                case '-': break;
                default: throw std::range_error("Could not parse castling rights character '" +
                                                std::string(1, character) + "' at position " +
                                                getCurrentPosition() + "!");
            }

            character = getNextCharacter();
        }
    }

    GameState FenParser::parse(std::string_view fen)
    {
        GameState gameState;
        gameState.board.bitboards = {};
        gameState.board.occupancies = {};

        beginPos = fen.begin();
        currentPos = fen.begin();
        endPos = fen.end();

        char character;

        // FEN strings begin at the top left (a8) and continue to the right position
        for (int rank = 7; rank >= 0; --rank)
        {
            for (int file = 0; file < 8; )
            {
                const Square square = BitBoardOperations::getSquare(rank, file);

                character = *currentPos;

                // match ascii pieces within FEN string
                if (isAlphabetic(character))
                {
                    // init figureType type
                    const ColoredFigureType figureType = charToFigureType(character);

                    // set figureType on corresponding bitboard
                    gameState.board.bitboards[figureType] = BitBoardOperations::occupySquare(gameState.board.bitboards[figureType], square);

                    character = getNextCharacter();
                    ++file;
                }
                // match empty square numbers within FEN string
                else if (isRankNumber(character))
                {
                    // init offset (convert char 0 to int 0)
                    const int offset = character - '0';

                    // adjust file counter
                    file += offset;

                    character = getNextCharacter();
                }

                const bool characterIsRankSeparator = (character == '/');

                if (characterIsRankSeparator)
                {
                    nextPosition();
                }
            }
        }

        // got to parsing side to move (increment pointer to FEN string)
        character = getNextCharacter();

        // parse side to move
        gameState.sideToMove = parseColor(character);

        // go to parsing castling rights
        nextPosition();
        parseCastlingRights(gameState);

        // got to parsing en passant square
        nextPosition();

        // parse en passant square
        gameState.enPassantTarget = parseSquare();

        // Skip space and parse half moves
        nextPosition();
        gameState.halfMoveClock = parseNumber();

        // Skip space and parse number of next move
        nextPosition();
        gameState.nextMoveClock = parseNumber();

        initOccupancyMaps(gameState);

        return gameState;
    }

    void FenParser::initOccupancyMaps(GameState &gameState)
    {
        // Init white occupancy map
        for (ColoredFigureType figureType = ColoredFigureType::WhitePawn; figureType <= ColoredFigureType::WhiteKing; ++figureType)
        {
            gameState.board.occupancies[Color::White] |= gameState.board.bitboards[figureType];
        }

        // Init black occupancy map
        for (ColoredFigureType figureType = ColoredFigureType::BlackPawn; figureType <= ColoredFigureType::BlackKing; ++figureType)
        {
            gameState.board.occupancies[Color::Black] |= gameState.board.bitboards[figureType];
        }

        // init all occupancies
        gameState.board.occupancies[Color::Both] |= gameState.board.occupancies[Color::White];
        gameState.board.occupancies[Color::Both] |= gameState.board.occupancies[Color::Black];
    }
}