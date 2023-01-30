set(target modern-chess-lib)



add_library(${target}
        ../include/ModernChess/BitBoard.h
        ../include/ModernChess/BitBoardConstants.h

        BitBoard.cpp
        )

target_include_directories(${target} PUBLIC ../include)

