#include "ModernChess/Move.h"
#include "ModernChess/TUI.h"

namespace ModernChess {

}

std::ostream& operator<<(std::ostream& os, ModernChess::Move move)
{
    using namespace ModernChess;

    os << squareToCoordinates[move.getFrom()];
    os << squareToCoordinates[move.getTo()];

    const char promotedPiece = TUI::promotedPieceToCharacter[move.getPromotedPiece()];

    if ('\0' != promotedPiece)
    {
        os << promotedPiece;
    }

    return os;
}