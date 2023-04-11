set(target modern-chess-lib)



add_library(${target}
        ../include/ModernChess/BitBoard.h
        ../include/ModernChess/BitBoardConstants.h
        ../include/ModernChess/BitBoardOperations.h
        ../include/ModernChess/BishopAttacks.h
        ../include/ModernChess/CastleRights.h
        ../include/ModernChess/Color.h
        ../include/ModernChess/Game.h
        ../include/ModernChess/GameState.h
        ../include/ModernChess/FenParsing.h
        ../include/ModernChess/Figure.h
        ../include/ModernChess/FlatMap.h
        ../include/ModernChess/KingAttacks.h
        ../include/ModernChess/KnightAttacks.h
        ../include/ModernChess/Move.h
        ../include/ModernChess/MoveGenerations.h
        ../include/ModernChess/PawnAttacks.h
        ../include/ModernChess/PawnQueries.h
        ../include/ModernChess/Player.h
        ../include/ModernChess/QueenAttacks.h
        ../include/ModernChess/RookAttacks.h
        ../include/ModernChess/Square.h
        ../include/ModernChess/Utilities.h

        BitBoard.cpp
        FenParsing.cpp
        Utilities.cpp
        Player.cpp
        GameState.cpp
        Game.cpp
        Move.cpp
        PawnAttacks.cpp
        RookAttacks.cpp
        BishopAttacks.cpp
        CastleRights.cpp
        )

target_include_directories(${target} PUBLIC ../include)

