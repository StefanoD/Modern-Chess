set(target modern-chess-lib-test)

add_executable(${target}
        AttacksGenerationTest.cpp
        BishopAttackGenerationTest.cpp
        BitBoardConstantsTest.cpp
        BitBoardOperationsTest.cpp
        BoardTest.cpp
        MoveGenerationsTest.cpp
        SquareTest.cpp
        PawnQueriesTest.cpp
        RookAttackGenerationTest.cpp
        MagicNumberCandidatesGeneration.cpp)

target_link_libraries(${target} PRIVATE
        GTest::gtest_main
        modern-chess-lib
        )

gtest_discover_tests(${target} WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin)