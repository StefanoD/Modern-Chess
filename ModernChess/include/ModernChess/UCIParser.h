#pragma once

#include "BasicParser.h"
#include "Move.h"

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

        /**
         * @note Because the UCI input has only the information about the move
         *       from a certain square, to a certain square and a possible promotion,
         *       only these listed information can be retrieved. All other information
         *       must not be queried from the returned Move object, because they are filled
         *       with dummy information.
         */
        [[nodiscard]] Move parseMove();

    private:
    };
}