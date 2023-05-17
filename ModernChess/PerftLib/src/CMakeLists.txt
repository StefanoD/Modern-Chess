set(target perft-lib)

add_library(${target}
        ../include/ModernChess/PerftLib/PerformanceTest.h

        PerformanceTest.cpp)

target_include_directories(${target} PUBLIC ../include)

target_link_libraries(${target} PRIVATE
        modern-chess-lib
        )