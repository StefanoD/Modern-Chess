set(target modern-chess-lib)



add_library(${target}
        ../include/ModernChess/BitBoard.h
        ../include/ModernChess/BitBoardConstants.h
        ../include/ModernChess/BitBoardState.h
        ../include/ModernChess/BitboardOperations.h
        ../include/ModernChess/MoveGeneration.h
        ../include/ModernChess/Square.h

        BitBoard.cpp
        MoveGeneration.cpp
        BitBoardState.cpp)

target_include_directories(${target} PUBLIC ../include)

