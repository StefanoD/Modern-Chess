#pragma once

#include "Move.h"

#include <string_view>

namespace ModernChess
{
    class UCIParser
    {
    public:
        Move parseMove(std::string_view &string) const
        {
            Move move{};



            return move;
        }
    private:
    };
}