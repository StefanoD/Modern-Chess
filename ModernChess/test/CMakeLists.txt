set(target modern-chess-lib-test)

add_executable(${target}
        PawnAttacksTest.cpp
        BishopAttacksTest.cpp
        BitBoardConstantsTest.cpp
        BitBoardOperationsTest.cpp
        BoardTest.cpp
        FenParsingTest.cpp
        GameStateTest.cpp
        MagicNumberCandidatesGeneration.cpp
        MoveGenerationsTest.cpp
        QueenAttacksTest.cpp
        PawnQueriesTest.cpp
        RookAttacksTest.cpp
        SquareTest.cpp
        )

target_link_libraries(${target} PRIVATE
        GTest::gtest_main
        modern-chess-lib
        )

gtest_discover_tests(${target} WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin)