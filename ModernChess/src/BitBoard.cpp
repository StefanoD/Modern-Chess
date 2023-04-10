#include "ModernChess/BitBoard.h"
#include "ModernChess/BitBoardOperations.h"
#include "ModernChess/FenParsing.h"

namespace ModernChess
{
    BitBoard::BitBoard()
    {


        bitboards[ColoredFigureType::WhiteRook] = BitBoardOperations::occupySquare(bitboards[ColoredFigureType::WhiteRook], Square::a1);
        bitboards[ColoredFigureType::WhiteRook] = BitBoardOperations::occupySquare(bitboards[ColoredFigureType::WhiteRook], Square::h1);

        bitboards[ColoredFigureType::WhiteKnight] = BitBoardOperations::occupySquare(bitboards[ColoredFigureType::WhiteKnight], Square::b1);
        bitboards[ColoredFigureType::WhiteKnight] = BitBoardOperations::occupySquare(bitboards[ColoredFigureType::WhiteKnight], Square::g1);

        bitboards[ColoredFigureType::WhiteBishop] = BitBoardOperations::occupySquare(bitboards[ColoredFigureType::WhiteBishop], Square::c1);
        bitboards[ColoredFigureType::WhiteBishop] = BitBoardOperations::occupySquare(bitboards[ColoredFigureType::WhiteBishop], Square::f1);

        bitboards[ColoredFigureType::WhiteQueen] = BitBoardOperations::occupySquare(bitboards[ColoredFigureType::WhiteQueen], Square::d1);
        bitboards[ColoredFigureType::WhiteKing] = BitBoardOperations::occupySquare(bitboards[ColoredFigureType::WhiteKing], Square::e1);

        for (Square square = Square::a2; square <= Square::h2; ++square)
        {
            bitboards[ColoredFigureType::WhitePawn] = BitBoardOperations::occupySquare(bitboards[ColoredFigureType::WhitePawn], Square(square));
        }

        // Black figures have essentially the same position, just rotated by 180 degrees
        bitboards[ColoredFigureType::BlackRook] = BitBoardOperations::rotate180(bitboards[ColoredFigureType::WhiteRook]);
        bitboards[ColoredFigureType::BlackKnight] = BitBoardOperations::rotate180(bitboards[ColoredFigureType::WhiteKnight]);
        bitboards[ColoredFigureType::BlackBishop] = BitBoardOperations::rotate180(bitboards[ColoredFigureType::WhiteBishop]);
        bitboards[ColoredFigureType::BlackQueen] = BitBoardOperations::rotate180(bitboards[ColoredFigureType::WhiteQueen]);
        bitboards[ColoredFigureType::BlackKing] = BitBoardOperations::rotate180(bitboards[ColoredFigureType::WhiteKing]);
        bitboards[ColoredFigureType::BlackPawn] = BitBoardOperations::rotate180(bitboards[ColoredFigureType::WhitePawn]);
    }

    BitBoardState BitBoard::getOccupiedSquares() const
    {
        return bitboards[ColoredFigureType::BlackRook] |
               bitboards[ColoredFigureType::BlackKnight] |
               bitboards[ColoredFigureType::BlackBishop] |
               bitboards[ColoredFigureType::BlackQueen] |
               bitboards[ColoredFigureType::BlackKing] |
               bitboards[ColoredFigureType::BlackPawn] |
               bitboards[ColoredFigureType::WhiteRook] |
               bitboards[ColoredFigureType::WhiteKnight] |
               bitboards[ColoredFigureType::WhiteBishop] |
               bitboards[ColoredFigureType::WhiteQueen] |
               bitboards[ColoredFigureType::WhiteKing] |
               bitboards[ColoredFigureType::WhitePawn];
    }

    BitBoardState BitBoard::getWhiteFigures() const
    {
        return bitboards[ColoredFigureType::WhiteRook] |
               bitboards[ColoredFigureType::WhiteKnight] |
               bitboards[ColoredFigureType::WhiteBishop] |
               bitboards[ColoredFigureType::WhiteQueen] |
               bitboards[ColoredFigureType::WhiteKing] |
               bitboards[ColoredFigureType::WhitePawn];
    }

    BitBoardState BitBoard::getBlackFigures() const
    {
        return bitboards[ColoredFigureType::BlackRook] |
               bitboards[ColoredFigureType::BlackKnight] |
               bitboards[ColoredFigureType::BlackBishop] |
               bitboards[ColoredFigureType::BlackQueen] |
               bitboards[ColoredFigureType::BlackKing] |
               bitboards[ColoredFigureType::BlackPawn];
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

            ColoredFigureType figureOnSquare = ColoredFigureType::None;

            // loop over all figures bitboards
            for (ColoredFigureType figure = WhitePawn; figure <= BlackKing; ++figure)
            {
                if (BitBoardOperations::isOccupied(bitBoard.bitboards[figure], square))
                {
                    figureOnSquare = figure;
                    break;
                }
            }

            // print different figureOnSquare set depending on OS
#ifdef WIN64
            os << " " << ((figureOnSquare == ColoredFigureType::None) ? "." : FenParsing::asciiFigures[figureOnSquare]);
#else
            os << " " << ((figureOnSquare == ColoredFigureType::None) ? "." : FenParsing::unicodeFigures[figureOnSquare]);
#endif
        }

        // print new line every rank
        os << std::endl;
    }

    // print board files
    os << std::endl << "    a b c d e f g h" << std::endl << std::endl;

    return os;
}