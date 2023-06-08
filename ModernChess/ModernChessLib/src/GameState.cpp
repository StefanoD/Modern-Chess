#include "ModernChess/GameState.h"

std::ostream& operator<<(std::ostream& os, const ModernChess::GameState &gameState)
{
    using namespace ModernChess;

    os << gameState.board;

    os << "Side to move: ";

    if (gameState.board.sideToMove == Color::White)
    {
        os << "white" << std::endl;
    }
    else
    {
        os << "black" << std::endl;
    }

    os << "En passant: ";
    if (gameState.board.enPassantTarget != Square::undefined)
    {
        os << squareToCoordinates[gameState.board.enPassantTarget] << std::endl;
    }
    else
    {
        os << "no" << std::endl;
    }

    os << gameState.board.castlingRights;

    return os;
}