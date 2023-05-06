#include "ModernChess/Move.h"
#include "ModernChess/FenParsing.h"

#include <array>

namespace ModernChess {
    /**
     * @brief UCI compliant promotion encoding
     */
    static constexpr std::array<char, 255> promotedPieceToCharacter = [] {
        std::array<char, 255> a{};
        a[Figure::WhiteKnight] = 'n';
        a[Figure::WhiteBishop] = 'b';
        a[Figure::WhiteRook] = 'r';
        a[Figure::WhiteQueen] = 'q';
        a[Figure::BlackKnight] = 'n';
        a[Figure::BlackBishop] = 'b';
        a[Figure::BlackRook] = 'r';
        a[Figure::BlackQueen] = 'q';
        return a;
    } ();
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

    const char promotedPiece = promotedPieceToCharacter[move.getPromotedPiece()];

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