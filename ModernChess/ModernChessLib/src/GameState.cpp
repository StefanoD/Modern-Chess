#include "ModernChess/GameState.h"

namespace ModernChess
{
    const ZobristHasher GameState::m_hasher{};
    TranspositionTable GameState::transpositionTable{};

    GameState::GameState()
    {
        transpositionTable.clear();
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

    os << gameState.board.castlingRights << std::endl;

    const std::ios::fmtflags os_flags (os.flags());
    os << "Hash key: " << std::hex << gameState.gameStateHash << std::endl;
    os.flags(os_flags);
    return os;
}