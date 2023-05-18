#pragma once

#include "BasicParser.h"
#include "GameState.h"
#include "Move.h"

#include <string_view>

namespace ModernChess
{
    class UCIParser : BasicParser
    {
    public:
        explicit UCIParser(std::string_view fen);

        [[nodiscard]] bool uiRequestsUCIMode() const;

        [[nodiscard]] bool uiRequestsNewGame() const;

        [[nodiscard]] bool uiIsReady() const;

        [[nodiscard]] bool uiQuitsGame() const;

        [[nodiscard]] bool uiHasSentPosition();

        [[nodiscard]] bool uiHasSentMoves();

        [[nodiscard]] bool uiHasSentFENPosition();

        [[nodiscard]] bool uiHasSentStartingPosition();

        [[nodiscard]] bool uiHasSentGoCommand();

        [[nodiscard]] bool uiHasSentSearchDepth();

    private:
    };
}