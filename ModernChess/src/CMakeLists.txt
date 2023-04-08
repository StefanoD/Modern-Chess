set(target modern-chess-lib)



add_library(${target}
        ../include/ModernChess/AttacksGeneration.h
        ../include/ModernChess/BitBoard.h
        ../include/ModernChess/BitBoardConstants.h
        ../include/ModernChess/BitBoardOperations.h
        ../include/ModernChess/BishopAttackGeneration.h
        ../include/ModernChess/FlatMap.h
        ../include/ModernChess/FenParsing.h
        ../include/ModernChess/Color.h
        ../include/ModernChess/Game.h
        ../include/ModernChess/GameState.h
        ../include/ModernChess/Figure.h
        ../include/ModernChess/KingAttackGeneration.h
        ../include/ModernChess/KnightAttackGeneration.h
        ../include/ModernChess/Move.h
        ../include/ModernChess/MoveGenerations.h
        ../include/ModernChess/PawnAttackGeneration.h
        ../include/ModernChess/PawnQueries.h
        ../include/ModernChess/Player.h
        ../include/ModernChess/RookAttackGeneration.h
        ../include/ModernChess/Square.h
        ../include/ModernChess/Utilities.h

        AttacksGeneration.cpp
        BitBoard.cpp
        Utilities.cpp
        Player.cpp
        GameState.cpp
        Game.cpp
        Move.cpp
        PawnAttackGeneration.cpp
        RookAttackGeneration.cpp
        BishopAttackGeneration.cpp
        )

target_include_directories(${target} PUBLIC ../include)

