#include "ModernChess/Utilities.h"
#include "ModernChess/BitboardOperations.h"

namespace ModernChess {
    std::ostream& print(std::ostream &os, const ModernChess::BitBoardState bitBoardState)
    {
        // The enumeration is actually mirrored. So correct this for printing.
        const BitBoardState mirroredBoard = BitBoardOperations::mirrorHorizontal(bitBoardState);

        for (Square square = Square::h8; square >= Square::a1; --square)
        {
            os << BitBoardOperations::isOccupied(mirroredBoard, Square(square));

            if (square % 8 == 0)
            {
                os << std::endl;
            }
        }

        return os;
    }
}
