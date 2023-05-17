project(modern-chess-lib
        VERSION ${VERSION}
        )

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(PerftLib)
add_subdirectory(Perft)
add_subdirectory(benchmarks)