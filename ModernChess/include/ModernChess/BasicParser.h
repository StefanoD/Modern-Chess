#pragma once

#include "BitBoardOperations.h"
#include "Square.h"

#include <string_view>
#include <string>

namespace ModernChess
{
    class BasicParser
    {
    public:
        explicit BasicParser(std::string_view fen);

        [[nodiscard]] Square parseSquare();

    protected:
        std::string_view::iterator beginPos{};
        std::string_view::iterator currentPos{};
        std::string_view::iterator endPos{};

        static bool isAlphabetic(char character)
        {
            return (character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z');
        }

        static bool isNumerical(char character)
        {
            return character >= '0' && character <= '9';
        }

        [[nodiscard]] std::string getCurrentPosition() const;

        [[nodiscard]] bool isRankNumber(char character) const;

        void nextPosition();

        char getNextCharacter();

        bool hasNextCharacter();
    };
}