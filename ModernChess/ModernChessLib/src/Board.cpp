#include "ModernChess/Board.h"
#include "ModernChess/BitBoardOperations.h"
#include "ModernChess/FenParsing.h"

namespace ModernChess
{

    bool operator==(const Board &lhs, const Board &rhs)
    {
        return lhs.bitboards == rhs.bitboards &&
               lhs.occupancies == rhs.occupancies &&
               lhs.castlingRights == rhs.castlingRights &&
               lhs.enPassantTarget == rhs.enPassantTarget &&
               lhs.sideToMove == rhs.sideToMove;
    }

    bool operator!=(const Board &lhs, const Board &rhs)
    {
        return !(lhs == rhs);
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