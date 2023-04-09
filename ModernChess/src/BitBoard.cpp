#include "ModernChess/BitBoard.h"
#include "ModernChess/BitBoardOperations.h"
#include "ModernChess/FenParsing.h"

namespace ModernChess
{
    BitBoard::BitBoard()
    {


        bitboards[ColoredFigureTypes::WhiteRook] = BitBoardOperations::occupySquare(bitboards[ColoredFigureTypes::WhiteRook], Square::a1);
        bitboards[ColoredFigureTypes::WhiteRook] = BitBoardOperations::occupySquare(bitboards[ColoredFigureTypes::WhiteRook], Square::h1);

        bitboards[ColoredFigureTypes::WhiteKnight] = BitBoardOperations::occupySquare(bitboards[ColoredFigureTypes::WhiteKnight], Square::b1);
        bitboards[ColoredFigureTypes::WhiteKnight] = BitBoardOperations::occupySquare(bitboards[ColoredFigureTypes::WhiteKnight], Square::g1);

        bitboards[ColoredFigureTypes::WhiteBishop] = BitBoardOperations::occupySquare(bitboards[ColoredFigureTypes::WhiteBishop], Square::c1);
        bitboards[ColoredFigureTypes::WhiteBishop] = BitBoardOperations::occupySquare(bitboards[ColoredFigureTypes::WhiteBishop], Square::f1);

        bitboards[ColoredFigureTypes::WhiteQueen] = BitBoardOperations::occupySquare(bitboards[ColoredFigureTypes::WhiteQueen], Square::d1);
        bitboards[ColoredFigureTypes::WhiteKing] = BitBoardOperations::occupySquare(bitboards[ColoredFigureTypes::WhiteKing], Square::e1);

        for (Square square = Square::a2; square <= Square::h2; ++square)
        {
            bitboards[ColoredFigureTypes::WhitePawn] = BitBoardOperations::occupySquare(bitboards[ColoredFigureTypes::WhitePawn], Square(square));
        }

        // Black figures have essentially the same position, just rotated by 180 degrees
        bitboards[ColoredFigureTypes::BlackRook] = BitBoardOperations::rotate180(bitboards[ColoredFigureTypes::WhiteRook]);
        bitboards[ColoredFigureTypes::BlackKnight] = BitBoardOperations::rotate180(bitboards[ColoredFigureTypes::WhiteKnight]);
        bitboards[ColoredFigureTypes::BlackBishop] = BitBoardOperations::rotate180(bitboards[ColoredFigureTypes::WhiteBishop]);
        bitboards[ColoredFigureTypes::BlackQueen] = BitBoardOperations::rotate180(bitboards[ColoredFigureTypes::WhiteQueen]);
        bitboards[ColoredFigureTypes::BlackKing] = BitBoardOperations::rotate180(bitboards[ColoredFigureTypes::WhiteKing]);
        bitboards[ColoredFigureTypes::BlackPawn] = BitBoardOperations::rotate180(bitboards[ColoredFigureTypes::WhitePawn]);
    }

    BitBoardState BitBoard::getOccupiedSquares() const
    {
        return bitboards[ColoredFigureTypes::BlackRook]  |
               bitboards[ColoredFigureTypes::BlackKnight]  |
               bitboards[ColoredFigureTypes::BlackBishop]  |
               bitboards[ColoredFigureTypes::BlackQueen]  |
               bitboards[ColoredFigureTypes::BlackKing]  |
               bitboards[ColoredFigureTypes::BlackPawn]  |
               bitboards[ColoredFigureTypes::WhiteRook] |
               bitboards[ColoredFigureTypes::WhiteKnight] |
               bitboards[ColoredFigureTypes::WhiteBishop] |
               bitboards[ColoredFigureTypes::WhiteQueen] |
               bitboards[ColoredFigureTypes::WhiteKing] |
               bitboards[ColoredFigureTypes::WhitePawn];
    }

    BitBoardState BitBoard::getWhiteFigures() const
    {
        return bitboards[ColoredFigureTypes::WhiteRook] |
               bitboards[ColoredFigureTypes::WhiteKnight] |
               bitboards[ColoredFigureTypes::WhiteBishop] |
               bitboards[ColoredFigureTypes::WhiteQueen] |
               bitboards[ColoredFigureTypes::WhiteKing] |
               bitboards[ColoredFigureTypes::WhitePawn];
    }

    BitBoardState BitBoard::getBlackFigures() const
    {
        return bitboards[ColoredFigureTypes::BlackRook]  |
               bitboards[ColoredFigureTypes::BlackKnight]  |
               bitboards[ColoredFigureTypes::BlackBishop]  |
               bitboards[ColoredFigureTypes::BlackQueen]  |
               bitboards[ColoredFigureTypes::BlackKing]  |
               bitboards[ColoredFigureTypes::BlackPawn];
    }

    BitBoardState BitBoard::getEmptySquares() const
    {
        return ~getOccupiedSquares();
    }
}

std::ostream& operator<<(std::ostream& os, const ModernChess::BitBoard &bitBoard)
{
    using namespace ModernChess;

    os << std::endl;

    for (int rank = 0; rank < 8; ++rank)
    {
        for (int file = 0; file < 8; ++file)
        {
            const Square square = BitBoardOperations::getSquare(rank, file);

            // print ranks
            if (file == 0)
            {
                os << "  " << (8 - rank);
            }

            ColoredFigureTypes figureOnSquare = ColoredFigureTypes::None;

            // loop over all figures bitboards
            for (ColoredFigureTypes figure = WhitePawn; figure <= BlackKing; ++figure)
            {
                if (BitBoardOperations::isOccupied(bitBoard.bitboards[figure], square))
                {
                    figureOnSquare = figure;
                    break;
                }
            }

            // print different figureOnSquare set depending on OS
#ifdef WIN64
            os << " " << ((figureOnSquare == ColoredFigureTypes::None) ? "." : FenParsing::asciiFigures[figureOnSquare]);
#else
            os << " " << ((figureOnSquare == ColoredFigureTypes::None) ? "." : FenParsing::unicodeFigures[figureOnSquare]);
#endif
        }

        // print new line every rank
        os << std::endl;
    }

    // print board files
    os << std::endl << "    a b c d e f g h" << std::endl << std::endl;

    return os;
}