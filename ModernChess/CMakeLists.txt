project(modern-chess-lib
        VERSION ${VERSION}
        )

add_subdirectory(benchmarks)
add_subdirectory(ModernChessLib)
add_subdirectory(test)
add_subdirectory(PerftLib)
add_subdirectory(Perft)
add_subdirectory(ModernChess)