#include "ModernChess/CastleRights.h"

std::ostream& operator<<(std::ostream& os, const ModernChess::CastleRights castleRights)
{
    using namespace ModernChess;

    os << "Castling Rights:" << std::endl;

    os << "\tWhite:";

    if (whiteCanKingSideCastle(castleRights))
    {
        os << " king-side";
    }
    if (whiteCanQueenSideCastle(castleRights))
    {
        os << " queen-side";
    }

    if (not whiteCanKingSideCastle(castleRights) and
        not whiteCanQueenSideCastle(castleRights))
    {
        os << " castling not possible";
    }

    os << std::endl;
    os << "\tBlack:";

    if (blackCanKingSideCastle(castleRights))
    {
        os << " king-side";
    }
    if (blackCanQueenSideCastle(castleRights))
    {
        os << " queen-side";
    }

    if (not blackCanKingSideCastle(castleRights) and
        not blackCanQueenSideCastle(castleRights))
    {
        os << " castling not possible";
    }

    return os;
}