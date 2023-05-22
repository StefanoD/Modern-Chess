#include "ModernChess/GameState.h"

namespace ModernChess
{

    GameState::GameState()
    {
        //moveList.reserve(256);
    }

    bool operator==(const GameState &lhs, const GameState &rhs)
    {
        return lhs.board == rhs.board &&
               lhs.halfMoveClock == rhs.halfMoveClock &&
               lhs.nextMoveClock == rhs.nextMoveClock;
    }

    bool operator!=(const GameState &lhs, const GameState &rhs)
    {
        return !(lhs == rhs);
    }
}

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