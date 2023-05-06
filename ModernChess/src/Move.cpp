#include "ModernChess/Move.h"
#include "ModernChess/TUI.h"
#include "ModernChess/FenParsing.h"

namespace ModernChess {

}

std::ostream& operator<<(std::ostream& os, ModernChess::Move move)
{
    using namespace ModernChess;

    if (move.isNullMove())
    {
        // UCI compliant NULL move
        os << "0000";
        return os;
    }

    os << squareToCoordinates[move.getFrom()];
    os << squareToCoordinates[move.getTo()];

    const char promotedPiece = TUI::promotedPieceToCharacter[move.getPromotedPiece()];

    if ('\0' != promotedPiece)
    {
        os << promotedPiece;
    }

    return os;
}

std::ostream &operator<<(std::ostream &os, const std::vector<ModernChess::Move> &moves)
{
    using namespace ModernChess;

    os << "#\t\tmove\tfigure\tcapture\tdouble-push\ten-passant\tcastling\n\n";

    int32_t moveCounter = 0;

    for (const Move move : moves)
    {
        os << moveCounter << "\t\t";
        os << move << "\t";

#ifdef WIN64
        os << "  " << FenParsing::asciiFigures[move.getMovedFigure()] << "\t\t";
#else
        os << "  " << FenParsing::unicodeFigures[move.getMovedFigure()] << "\t\t";
#endif

        os << (move.isCapture() ? "true" : "false") << "\t";
        os << (move.isDoublePawnPush() ? "true" : "false") << "\t\t";
        os << (move.isEnPassantCapture() ? "true" : "false") << "\t\t";
        os << (move.isCastlingMove() ? "true" : "false") << std::endl;

        ++moveCounter;
    }

    return os;
}