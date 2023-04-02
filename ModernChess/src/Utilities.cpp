#include "ModernChess/Utilities.h"
#include "ModernChess/BitBoardOperations.h"

using namespace ModernChess;

std::ostream &print(std::ostream &os, const BitBoardState bitBoardState)
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

uint32_t getRandomNumber()
{
    // pseudo random number state
    static uint32_t state = 1804289383;

    // get current state
    uint32_t number = state;

    // XOR shift algorithm
    number ^= number << 13;
    number ^= number >> 17;
    number ^= number << 5;

    // update random number state
    state = number;

    // return random number
    return number;
}