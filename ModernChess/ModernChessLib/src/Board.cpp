#include "ModernChess/Board.h"
#include "ModernChess/BitBoardOperations.h"
#include "ModernChess/FenParsing.h"

namespace ModernChess
{
    Board::Board()
    {


        bitboards[Figure::WhiteRook] = BitBoardOperations::occupySquare(bitboards[Figure::WhiteRook], Square::a1);
        bitboards[Figure::WhiteRook] = BitBoardOperations::occupySquare(bitboards[Figure::WhiteRook], Square::h1);

        bitboards[Figure::WhiteKnight] = BitBoardOperations::occupySquare(bitboards[Figure::WhiteKnight], Square::b1);
        bitboards[Figure::WhiteKnight] = BitBoardOperations::occupySquare(bitboards[Figure::WhiteKnight], Square::g1);

        bitboards[Figure::WhiteBishop] = BitBoardOperations::occupySquare(bitboards[Figure::WhiteBishop], Square::c1);
        bitboards[Figure::WhiteBishop] = BitBoardOperations::occupySquare(bitboards[Figure::WhiteBishop], Square::f1);

        bitboards[Figure::WhiteQueen] = BitBoardOperations::occupySquare(bitboards[Figure::WhiteQueen], Square::d1);
        bitboards[Figure::WhiteKing] = BitBoardOperations::occupySquare(bitboards[Figure::WhiteKing], Square::e1);

        for (Square square = Square::a2; square <= Square::h2; ++square)
        {
            bitboards[Figure::WhitePawn] = BitBoardOperations::occupySquare(bitboards[Figure::WhitePawn], Square(square));
        }

        // Black figures have essentially the same position, just rotated by 180 degrees
        bitboards[Figure::BlackRook] = BitBoardOperations::rotate180(bitboards[Figure::WhiteRook]);
        bitboards[Figure::BlackKnight] = BitBoardOperations::rotate180(bitboards[Figure::WhiteKnight]);
        bitboards[Figure::BlackBishop] = BitBoardOperations::rotate180(bitboards[Figure::WhiteBishop]);
        bitboards[Figure::BlackQueen] = BitBoardOperations::rotate180(bitboards[Figure::WhiteQueen]);
        bitboards[Figure::BlackKing] = BitBoardOperations::rotate180(bitboards[Figure::WhiteKing]);
        bitboards[Figure::BlackPawn] = BitBoardOperations::rotate180(bitboards[Figure::WhitePawn]);
    }

    BitBoardState Board::getOccupiedSquares() const
    {
        return bitboards[Figure::BlackRook] |
               bitboards[Figure::BlackKnight] |
               bitboards[Figure::BlackBishop] |
               bitboards[Figure::BlackQueen] |
               bitboards[Figure::BlackKing] |
               bitboards[Figure::BlackPawn] |
               bitboards[Figure::WhiteRook] |
               bitboards[Figure::WhiteKnight] |
               bitboards[Figure::WhiteBishop] |
               bitboards[Figure::WhiteQueen] |
               bitboards[Figure::WhiteKing] |
               bitboards[Figure::WhitePawn];
    }

    BitBoardState Board::getWhiteFigures() const
    {
        return bitboards[Figure::WhiteRook] |
               bitboards[Figure::WhiteKnight] |
               bitboards[Figure::WhiteBishop] |
               bitboards[Figure::WhiteQueen] |
               bitboards[Figure::WhiteKing] |
               bitboards[Figure::WhitePawn];
    }

    BitBoardState Board::getBlackFigures() const
    {
        return bitboards[Figure::BlackRook] |
               bitboards[Figure::BlackKnight] |
               bitboards[Figure::BlackBishop] |
               bitboards[Figure::BlackQueen] |
               bitboards[Figure::BlackKing] |
               bitboards[Figure::BlackPawn];
    }

    BitBoardState Board::getEmptySquares() const
    {
        return ~getOccupiedSquares();
    }
}

std::ostream& operator<<(std::ostream& os, const ModernChess::Board &bitBoard)
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

            Figure figureOnSquare = Figure::None;

            // loop over all figures bitboards
            for (Figure figure = WhitePawn; figure <= BlackKing; ++figure)
            {
                if (BitBoardOperations::isOccupied(bitBoard.bitboards[figure], square))
                {
                    figureOnSquare = figure;
                    break;
                }
            }

            // print different figureOnSquare set depending on OS
#ifdef WIN64
            os << " " << ((figureOnSquare == Figure::None) ? "." : FenParsing::asciiFigures[figureOnSquare]);
#else
            os << " " << ((figureOnSquare == Figure::None) ? "." : FenParsing::unicodeFigures[figureOnSquare]);
#endif
        }

        // print new line every rank
        os << std::endl;
    }

    // print board files
    os << std::endl << "    a b c d e f g h" << std::endl << std::endl;

    return os;
}