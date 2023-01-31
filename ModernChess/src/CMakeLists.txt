set(target modern-chess-lib)



add_library(${target}
        ../include/ModernChess/BitBoard.h
        ../include/ModernChess/BitBoardConstants.h
        ../include/ModernChess/MoveGeneration.h
        ../include/ModernChess/BitboardOperations.h

        BitBoard.cpp
        MoveGeneration.cpp
        )

target_include_directories(${target} PUBLIC ../include)

