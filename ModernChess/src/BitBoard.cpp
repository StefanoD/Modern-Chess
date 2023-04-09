#include "ModernChess/BitBoard.h"
#include "ModernChess/BitBoardOperations.h"
#include "ModernChess/FenParsing.h"

namespace ModernChess
{
    BitBoard::BitBoard()
    {
        m_whiteRookBitBoard = BitBoardOperations::occupySquare(m_whiteRookBitBoard, Square::a1);
        m_whiteRookBitBoard = BitBoardOperations::occupySquare(m_whiteRookBitBoard, Square::h1);

        m_whiteKnightBitBoard = BitBoardOperations::occupySquare(m_whiteKnightBitBoard, Square::b1);
        m_whiteKnightBitBoard = BitBoardOperations::occupySquare(m_whiteKnightBitBoard, Square::g1);

        m_whiteBishopBitBoard = BitBoardOperations::occupySquare(m_whiteBishopBitBoard, Square::c1);
        m_whiteBishopBitBoard = BitBoardOperations::occupySquare(m_whiteBishopBitBoard, Square::f1);

        m_whiteQueenBitBoard = BitBoardOperations::occupySquare(m_whiteQueenBitBoard, Square::d1);
        m_whiteKingBitBoard = BitBoardOperations::occupySquare(m_whiteKingBitBoard, Square::e1);

        for (Square square = Square::a2; square <= Square::h2; ++square)
        {
            m_whitePawnBitBoard = BitBoardOperations::occupySquare(m_whitePawnBitBoard, Square(square));
        }

        // Black figures have essentially the same position, just rotated by 180 degrees
        m_blackRookBitBoard = BitBoardOperations::rotate180(m_whiteRookBitBoard);
        m_blackKnightBitBoard = BitBoardOperations::rotate180(m_whiteKnightBitBoard);
        m_blackBishopBitBoard = BitBoardOperations::rotate180(m_whiteBishopBitBoard);
        m_blackQueenBitBoard = BitBoardOperations::rotate180(m_whiteQueenBitBoard);
        m_blackKingBitBoard = BitBoardOperations::rotate180(m_whiteKingBitBoard);
        m_blackPawnBitBoard = BitBoardOperations::rotate180(m_whitePawnBitBoard);
    }

    BitBoardState BitBoard::getOccupiedSquares() const
    {
        return m_blackRookBitBoard |
               m_blackKnightBitBoard |
               m_blackBishopBitBoard |
               m_blackQueenBitBoard |
               m_blackKingBitBoard |
               m_blackPawnBitBoard |
               m_whiteRookBitBoard |
               m_whiteKnightBitBoard |
               m_whiteBishopBitBoard |
               m_whiteQueenBitBoard |
               m_whiteKingBitBoard |
               m_whitePawnBitBoard;
    }

    BitBoardState BitBoard::getWhiteFigures() const
    {
        return m_whiteRookBitBoard |
               m_whiteKnightBitBoard |
               m_whiteBishopBitBoard |
               m_whiteQueenBitBoard |
               m_whiteKingBitBoard |
               m_whitePawnBitBoard;
    }

    BitBoardState BitBoard::getBlackFigures() const
    {
        return m_blackRookBitBoard |
               m_blackKnightBitBoard |
               m_blackBishopBitBoard |
               m_blackQueenBitBoard |
               m_blackKingBitBoard |
               m_blackPawnBitBoard;
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

    for (int rank = 0; rank < 8; ++rank)
    {
        for (int file = 0; file < 8; ++file)
        {
            const Square square = BitBoardOperations::getSquare(rank, file);

            // print ranks
            if (file != 0)
            {
                os << "  " << (8 - rank);
            }

            ColoredFigureTypes figureOnSquare = ColoredFigureTypes::None;

            // loop over all figures bitboards
            for (ColoredFigureTypes figure = WhitePawn; figure <= BlackKing; ++figure)
            {
                if (BitBoardOperations::isOccupied(bitBoard.bitboards[figure], square))
                {
                    figureOnSquare = figure;
                    break;
                }
            }

            // print different figureOnSquare set depending on OS
#ifdef WIN64
            os << " " << ((figureOnSquare == ColoredFigureTypes::None) ? "." : FenParsing::asciiFigures[figureOnSquare]);
#else
            os << " " << ((figureOnSquare == ColoredFigureTypes::None) ? "." : FenParsing::unicodeFigures[figureOnSquare]);
#endif
        }

        // print new line every rank
        os << std::endl;
    }

    // print board files
    os << std::endl << "     a b c d e f g h" << std::endl << std::endl;

    return os;
}