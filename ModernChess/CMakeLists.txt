project(modern-chess-lib
        VERSION ${VERSION}
        )

SET(BENCHMARK_ENABLE_TESTING OFF)

IF (${BENCHMARK_ENABLE_TESTING})
    add_subdirectory(benchmarks)
ENDIF ()

add_subdirectory(ModernChessLib)
add_subdirectory(test)
add_subdirectory(PerftLib)
add_subdirectory(Perft)
add_subdirectory(ModernChess)