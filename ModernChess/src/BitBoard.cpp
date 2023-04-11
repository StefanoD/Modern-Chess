#include "ModernChess/BitBoard.h"
#include "ModernChess/BitBoardOperations.h"
#include "ModernChess/FenParsing.h"

namespace ModernChess
{
    BitBoard::BitBoard()
    {


        bitboards[FigureType::WhiteRook] = BitBoardOperations::occupySquare(bitboards[FigureType::WhiteRook], Square::a1);
        bitboards[FigureType::WhiteRook] = BitBoardOperations::occupySquare(bitboards[FigureType::WhiteRook], Square::h1);

        bitboards[FigureType::WhiteKnight] = BitBoardOperations::occupySquare(bitboards[FigureType::WhiteKnight], Square::b1);
        bitboards[FigureType::WhiteKnight] = BitBoardOperations::occupySquare(bitboards[FigureType::WhiteKnight], Square::g1);

        bitboards[FigureType::WhiteBishop] = BitBoardOperations::occupySquare(bitboards[FigureType::WhiteBishop], Square::c1);
        bitboards[FigureType::WhiteBishop] = BitBoardOperations::occupySquare(bitboards[FigureType::WhiteBishop], Square::f1);

        bitboards[FigureType::WhiteQueen] = BitBoardOperations::occupySquare(bitboards[FigureType::WhiteQueen], Square::d1);
        bitboards[FigureType::WhiteKing] = BitBoardOperations::occupySquare(bitboards[FigureType::WhiteKing], Square::e1);

        for (Square square = Square::a2; square <= Square::h2; ++square)
        {
            bitboards[FigureType::WhitePawn] = BitBoardOperations::occupySquare(bitboards[FigureType::WhitePawn], Square(square));
        }

        // Black figures have essentially the same position, just rotated by 180 degrees
        bitboards[FigureType::BlackRook] = BitBoardOperations::rotate180(bitboards[FigureType::WhiteRook]);
        bitboards[FigureType::BlackKnight] = BitBoardOperations::rotate180(bitboards[FigureType::WhiteKnight]);
        bitboards[FigureType::BlackBishop] = BitBoardOperations::rotate180(bitboards[FigureType::WhiteBishop]);
        bitboards[FigureType::BlackQueen] = BitBoardOperations::rotate180(bitboards[FigureType::WhiteQueen]);
        bitboards[FigureType::BlackKing] = BitBoardOperations::rotate180(bitboards[FigureType::WhiteKing]);
        bitboards[FigureType::BlackPawn] = BitBoardOperations::rotate180(bitboards[FigureType::WhitePawn]);
    }

    BitBoardState BitBoard::getOccupiedSquares() const
    {
        return bitboards[FigureType::BlackRook] |
               bitboards[FigureType::BlackKnight] |
               bitboards[FigureType::BlackBishop] |
               bitboards[FigureType::BlackQueen] |
               bitboards[FigureType::BlackKing] |
               bitboards[FigureType::BlackPawn] |
               bitboards[FigureType::WhiteRook] |
               bitboards[FigureType::WhiteKnight] |
               bitboards[FigureType::WhiteBishop] |
               bitboards[FigureType::WhiteQueen] |
               bitboards[FigureType::WhiteKing] |
               bitboards[FigureType::WhitePawn];
    }

    BitBoardState BitBoard::getWhiteFigures() const
    {
        return bitboards[FigureType::WhiteRook] |
               bitboards[FigureType::WhiteKnight] |
               bitboards[FigureType::WhiteBishop] |
               bitboards[FigureType::WhiteQueen] |
               bitboards[FigureType::WhiteKing] |
               bitboards[FigureType::WhitePawn];
    }

    BitBoardState BitBoard::getBlackFigures() const
    {
        return bitboards[FigureType::BlackRook] |
               bitboards[FigureType::BlackKnight] |
               bitboards[FigureType::BlackBishop] |
               bitboards[FigureType::BlackQueen] |
               bitboards[FigureType::BlackKing] |
               bitboards[FigureType::BlackPawn];
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

    for (int rank = 7; rank >=0; --rank)
    {
        for (int file = 0; file < 8; ++file)
        {
            const Square square = BitBoardOperations::getSquare(rank, file);

            // print ranks
            if (file == 0)
            {
                os << "  " << (rank + 1);
            }

            FigureType figureOnSquare = FigureType::None;

            // loop over all figures bitboards
            for (FigureType figure = WhitePawn; figure <= BlackKing; ++figure)
            {
                if (BitBoardOperations::isOccupied(bitBoard.bitboards[figure], square))
                {
                    figureOnSquare = figure;
                    break;
                }
            }

            // print different figureOnSquare set depending on OS
#ifdef WIN64
            os << " " << ((figureOnSquare == FigureType::None) ? "." : FenParsing::asciiFigures[figureOnSquare]);
#else
            os << " " << ((figureOnSquare == FigureType::None) ? "." : FenParsing::unicodeFigures[figureOnSquare]);
#endif
        }

        // print new line every rank
        os << std::endl;
    }

    // print board files
    os << std::endl << "    a b c d e f g h" << std::endl << std::endl;

    return os;
}