#include "ModernChess/GameState.h"

namespace ModernChess
{

    GameState::GameState()
    {
        moveList.reserve(256);
    }
}

std::ostream& operator<<(std::ostream& os, const ModernChess::GameState &gameState)
{
    using namespace ModernChess;

    os << gameState.board;

    os << "Side to move: ";

    if (gameState.sideToMove == Color::White)
    {
        os << "white" << std::endl;
    }
    else
    {
        os << "black" << std::endl;
    }

    os << "En passant: ";
    if (gameState.enPassantTarget != Square::undefined)
    {
        os << squareToCoordinates[gameState.enPassantTarget] << std::endl;
    }
    else
    {
        os << "no" << std::endl;
    }

    os << gameState.castleRights;

    return os;
}