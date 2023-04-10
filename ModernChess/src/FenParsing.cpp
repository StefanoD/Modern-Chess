#include "ModernChess/FenParsing.h"
#include "ModernChess/BitBoardOperations.h"

#include <sstream>

using namespace ModernChess;

namespace ModernChess::FenParsing {

    std::string getCurrentPosition(std::string_view::iterator beginPos, std::string_view::iterator currentPos)
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

    bool isRankNumber(std::string_view::iterator beginPos,
                      std::string_view::iterator currentPos,
                      char character)
    {
        if (character == '9')
        {
            throw std::range_error("Invalid rank number '9' at position " +
                                   getCurrentPosition(beginPos, currentPos) + "!");
        }

        return isNumerical(character);
    }

    void nextPosition(std::string_view::iterator beginPos,
                      std::string_view::iterator &currentPos,
                      std::string_view::iterator endPos)
    {
        ++currentPos;
        if (currentPos == endPos)
        {
            const std::string position = getCurrentPosition(beginPos, currentPos);
            throw std::range_error("Error at position " + position + ": Unexpected end of line!");
        }
    }

    char getNextCharacter(std::string_view::iterator beginPos,
                          std::string_view::iterator &currentPos,
                          std::string_view::iterator endPos)
    {
        ++currentPos;
        if (currentPos == endPos)
        {
            const std::string position = getCurrentPosition(beginPos, currentPos);
            throw std::range_error("Error at position " + position + ": Unexpected end of line!");
        }
        return *currentPos;
    }

    bool hasNextCharacter(std::string_view::iterator currentPos,
                          std::string_view::iterator endPos)
    {
        return (currentPos+1) != endPos;
    }

    Color parseColor(std::string_view::iterator beginPos,
                     std::string_view::iterator currentPos,
                     char character)
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
                                   "' at position " + getCurrentPosition(beginPos, currentPos) + "!");
        }

        return color;
    }

    Square parseSquare(std::string_view::iterator beginPos,
                       std::string_view::iterator &currentPos,
                       std::string_view::iterator endPos)
    {
        char character = *currentPos;
        Square square = Square::undefined;

        if (isAlphabetic(character))
        {
            // parse en passant file & rank
            const int file = character - 'a';

            character = getNextCharacter(beginPos, currentPos, endPos);

            if (!isNumerical(character))
            {
                throw std::range_error("Could not parse square from character '" +
                                       std::string(1, character) + "' at position " + getCurrentPosition(beginPos, currentPos) +
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
                                   std::string(1, character) + "' at position " + getCurrentPosition(beginPos, currentPos) + "!");
        }

        return square;
    }

    uint32_t parseNumber(std::string_view::iterator beginPos,
                         std::string_view::iterator &currentPos,
                         std::string_view::iterator endPos)
    {
        std::stringstream strNumberHalfMoves;

        for (char character = getNextCharacter(beginPos, currentPos, endPos);
             isNumerical(character);
             character = getNextCharacter(beginPos, currentPos, endPos))
        {
            strNumberHalfMoves << character;

            if (!hasNextCharacter(currentPos, endPos))
            {
                break;
            }
        }

        uint32_t number = 0;
        strNumberHalfMoves >> number;

        if (strNumberHalfMoves.fail())
        {
            throw std::range_error("Could not parse number \"" + strNumberHalfMoves.str() +
                                   "\" at position " + getCurrentPosition(beginPos, currentPos) + "!");
        }

        // The last character was not a number. Therefore, decrement position again
        --currentPos;

        return number;
    }

    GameState parse(std::string_view fen)
    {
        GameState gameState;
        gameState.board.bitboards = {};
        gameState.board.occupancies = {};

        const auto *const beginPos = fen.begin();
        const auto *currentPos = fen.begin();
        const auto *const endPos = fen.end();

        char character;

        // FEN strings begin at the top left (a8) and continue to the right position
        for (int rank = 7; rank >= 0; --rank)
        {
            for (int file = 0; file < 8; ++file)
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

                    character = getNextCharacter(beginPos, currentPos, endPos);
                }

                // match empty square numbers within FEN string
                if (isRankNumber(beginPos, currentPos, character))
                {
                    // init offset (convert char 0 to int 0)
                    const int offset = character - '0';

                    // define figureOnSquare variable
                    ColoredFigureType figureOnSquare = ColoredFigureType::None;

                    // loop over all figureOnSquare bitboards
                    for (ColoredFigureType figureType = ColoredFigureType::WhitePawn; figureType <= ColoredFigureType::BlackKing; ++figureType)
                    {
                        if (BitBoardOperations::isOccupied(gameState.board.bitboards[figureType], square))
                        {
                            figureOnSquare = figureType;
                            break;
                        }
                    }

                    if (figureOnSquare == ColoredFigureType::None)
                    {
                        --file;
                    }

                    // adjust file counter
                    file += offset;

                    character = getNextCharacter(beginPos, currentPos, endPos);
                }

                // match rank separator
                if (character== '/')
                {
                    nextPosition(beginPos, currentPos, endPos);
                }
            }
        }

        // got to parsing side to move (increment pointer to FEN string)
        character = getNextCharacter(beginPos, currentPos, endPos);

        // parse side to move
        gameState.sideToMove = parseColor(beginPos, currentPos, character);

        // go to parsing castling rights
        nextPosition(beginPos, currentPos, endPos);
        character = getNextCharacter(beginPos, currentPos, endPos);

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
                                                getCurrentPosition(beginPos, currentPos) + "!");
            }

            character = getNextCharacter(beginPos, currentPos, endPos);
        }

        // got to parsing en passant square
        nextPosition(beginPos, currentPos, endPos);

        // parse en passant square
        gameState.enPassantTarget = parseSquare(beginPos, currentPos, endPos);

        // Skip space and parse half moves
        nextPosition(beginPos, currentPos, endPos);
        gameState.halfMoveClock = parseNumber(beginPos, currentPos, endPos);

        // Skip space and parse number of next move
        nextPosition(beginPos, currentPos, endPos);
        gameState.nextMoveClock = parseNumber(beginPos, currentPos, endPos);

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

        return gameState;
    }
}