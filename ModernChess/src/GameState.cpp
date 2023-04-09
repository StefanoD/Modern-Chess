#include "ModernChess/GameState.h"

namespace ModernChess
{

}

std::ostream& operator<<(std::ostream& os, const ModernChess::GameState &gameState)
{
    using namespace ModernChess;

    os << gameState.m_board;

    os << "Side to move: ";

    if (gameState.m_sideToMove == Color::White)
    {
        os << "white" << std::endl;
    }
    else
    {
        os << "black" << std::endl;
    }

    os << "Enpassant: ";
    if (gameState.m_enPassantTarget != Square::undefined)
    {
        os << squareToCoordinates[gameState.m_enPassantTarget] << std::endl;
    }
    else
    {
        os << "no" << std::endl;
    }

    os << gameState.castleRights;

    return os;
}