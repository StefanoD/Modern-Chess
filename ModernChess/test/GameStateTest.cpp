#include "ModernChess/GameState.h"

#include <gtest/gtest.h>

using namespace ModernChess;

namespace {
    TEST(GameStateTest, init)
    {
        const GameState gameState;

        std::cout << gameState;
    }
}