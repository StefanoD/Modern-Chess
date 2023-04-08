#pragma once

#include <array>
#include <string_view>

namespace ModernChess {
    // See https://de.wikipedia.org/wiki/Forsyth-Edwards-Notation

    // ASCII pieces
    constexpr auto asciiFigures = "PNBRQKpnbrqk";

    // unicode pieces
    constexpr std::array<std::string_view, 12> unicodeFigures {"♙", "♘", "♗", "♖", "♕", "♔", "♟︎", "♞", "♝", "♜", "♛", "♚"};
}