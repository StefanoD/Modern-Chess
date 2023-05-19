#pragma once

#include "BasicParser.h"

#include <string_view>

namespace ModernChess
{
    class UCIParser : public BasicParser
    {
    public:
        explicit UCIParser(std::string_view uiCommand);

        [[nodiscard]] bool uiRequestsUCIMode() const;

        [[nodiscard]] bool uiRequestsNewGame() const;

        [[nodiscard]] bool uiIsReady() const;

        [[nodiscard]] bool uiQuitGame() const;

        [[nodiscard]] bool uiHasSentPosition();

        [[nodiscard]] bool uiHasSentMoves();

        [[nodiscard]] bool uiHasSentFENPosition();

        [[nodiscard]] bool uiHasSentStartingPosition();

        [[nodiscard]] bool uiHasSentGoCommand();

        [[nodiscard]] bool uiHasSentSearchDepth();

    private:
    };
}