#include "ModernChess/BitBoardConstants.h"
#include "ModernChess/BitBoardOperations.h"

using namespace ModernChess;

std::ostream& operator<<(std::ostream& os, const ModernChess::BitBoardState bitBoardState)
{
    // The enumeration is actually mirrored. So correct this for printing.
    const BitBoardState mirroredBoard = BitBoardOperations::mirrorHorizontal(bitBoardState);

    os << "8 | ";

    for (Square square = Square::h8; square >= Square::a1; --square)
    {
        os << BitBoardOperations::isOccupied(mirroredBoard, Square(square)) << " ";

        if (square % 8 == 0)
        {
            os << std::endl;
            const int rank = square / 8;

            if (rank != 0)
            {
                os << rank << " | ";
            }

        }
    }
    os << "-------------------" << std::endl;
    os << "    a b c d e f g h" << std::endl;

    return os;
}