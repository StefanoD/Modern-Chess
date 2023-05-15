project(modern-chess-lib
        VERSION ${VERSION}
        )

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(perft)
add_subdirectory(benchmarks)