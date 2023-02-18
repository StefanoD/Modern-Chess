set(target modern-chess-lib)



add_library(${target}
        ../include/ModernChess/AttacksGeneration.h
        ../include/ModernChess/BitBoard.h
        ../include/ModernChess/BitBoardConstants.h
        ../include/ModernChess/BitBoardOperations.h
        ../include/ModernChess/Color.h
        ../include/ModernChess/MoveGenerations.h
        ../include/ModernChess/Player.h
        ../include/ModernChess/Square.h
        ../include/ModernChess/Utilities.h

        AttacksGeneration.cpp
        BitBoard.cpp
        Utilities.cpp
        Player.cpp
        )

target_include_directories(${target} PUBLIC ../include)

