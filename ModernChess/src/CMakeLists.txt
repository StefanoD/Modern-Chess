set(target modern-chess-lib)

add_library(${target}
        Board.cpp
        ../include/ModernChess/Board.h)

target_include_directories(${target} PUBLIC ../include)

