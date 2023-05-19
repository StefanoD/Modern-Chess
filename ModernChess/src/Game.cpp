#include "ModernChess/Game.h"

#include <utility>

namespace ModernChess
{
    Game::Game(GameState gameState) : m_gameState(std::move(gameState)) {}
}