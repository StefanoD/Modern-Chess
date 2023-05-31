set(target modern-chess-lib-benchmarks)

add_executable(${target}
        FenFigureToEnumConversionTest.cpp
        VectorReservationTest.cpp
        )

set(BENCHMARK_ENABLE_TESTING ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(benchmark REQUIRED)
find_package(Threads REQUIRED)

target_link_libraries(${target} PRIVATE
        benchmark::benchmark
        benchmark::benchmark_main
        Threads::Threads
        modern-chess-lib
        )