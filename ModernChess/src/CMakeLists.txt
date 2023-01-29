set(target modern-chess-lib)



add_library(${target}
        ../include/ModernChess/Board.h

        Board.cpp
        )

target_include_directories(${target} PUBLIC ../include)

