#include "ModernChess/FenParsing.h"
#include "ModernChess/BitBoardOperations.h"

using namespace ModernChess;

namespace ModernChess::FenParsing {

    bool isAlphabetic(char character)
    {
        return (character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z');
    }

    bool isNumerical(char character)
    {
        return character >= '0' && character <= '9';
    }

    void skipNextCharacter(std::string_view::iterator beginPos,
                           std::string_view::iterator &currentPos,
                           std::string_view::iterator endPos)
    {
        ++currentPos;
        if (currentPos == endPos)
        {
            const size_t position = currentPos - beginPos + 1;
            throw std::range_error("Error at position " + std::to_string(position) + ": Unexpected end of line!");
        }
    }

    char getNextCharacter(std::string_view::iterator beginPos,
                          std::string_view::iterator &currentPos,
                          std::string_view::iterator endPos)
    {
        ++currentPos;
        if (currentPos == endPos)
        {
            const size_t position = currentPos - beginPos + 1;
            throw std::range_error("Error at position " + std::to_string(position) + ": Unexpected end of line!");
        }
        return *currentPos;
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

        // FEN strings begin at the top left (a8)
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
                if (isNumerical(character))
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
                    skipNextCharacter(beginPos, currentPos, endPos);
                }
            }
        }

        // got to parsing side to move (increment pointer to FEN string)
        character = getNextCharacter(beginPos, currentPos, endPos);

        // parse side to move
        if (character == 'w')
        {
            gameState.sideToMove = Color::White;
        }
        else if (character == 'b')
        {
            gameState.sideToMove = Color::Black;
        }
        else
        {
            throw std::range_error("Expected 'w' or 'b' for side to move, but got '" + std::string(1, character) +
                "' at position" + std::to_string(currentPos - beginPos + 1) + "!");
        }
        // go to parsing castling rights
        skipNextCharacter(beginPos, currentPos, endPos);
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
                    std::string(1, character) + "' at position" + std::to_string(currentPos - beginPos + 1) + "!");
            }

            character = getNextCharacter(beginPos, currentPos, endPos);
        }

        // got to parsing en passant square (increment pointer to FEN string)
        character = getNextCharacter(beginPos, currentPos, endPos);

        // parse en passant square
        if (character != '-')
        {
            // parse en passant file & rank
            const int file = character - 'a';

            character = getNextCharacter(beginPos, currentPos, endPos);

            const int rank = 8 - (character - '0');

            // init en passant square
            gameState.enPassantTarget = BitBoardOperations::getSquare(rank, file);
        }
        else
        {
            gameState.enPassantTarget = Square::undefined;
        }

        // loop over white pieces bitboards
        for (ColoredFigureType figureType = ColoredFigureType::WhitePawn; figureType <= ColoredFigureType::WhiteKing; ++figureType)
        {    // populate white occupancy bitboard
            gameState.board.occupancies[Color::White] |= gameState.board.bitboards[figureType];
        }

        // loop over black pieces bitboards
        for (ColoredFigureType figureType = ColoredFigureType::BlackPawn; figureType <= ColoredFigureType::BlackKing; ++figureType)
        {    // populate white occupancy bitboard
            gameState.board.occupancies[Color::Black] |= gameState.board.bitboards[figureType];
        }

        // init all occupancies
        gameState.board.occupancies[Color::Both] |= gameState.board.occupancies[Color::White];
        gameState.board.occupancies[Color::Both] |= gameState.board.occupancies[Color::Black];

        return gameState;
    }
}