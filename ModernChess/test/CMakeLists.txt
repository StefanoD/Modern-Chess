set(target modern-chess-lib-test)

add_executable(${target}
        AttackQueriesTest.cpp
        PawnAttacksTest.cpp
        BishopAttacksTest.cpp
        BitBoardConstantsTest.cpp
        BitBoardOperationsTest.cpp
        BoardTest.cpp
        FenParsingTest.cpp
        GameStateTest.cpp
        MagicNumberCandidatesGeneration.cpp
        PawnPushesTest.cpp
        QueenAttacksTest.cpp
        PawnQueriesTest.cpp
        RookAttacksTest.cpp
        SquareTest.cpp
        MoveTest.cpp
        PseudoMoveGenerationTest.cpp
        UtilitiesTest.cpp CastleRightsTest.cpp)

target_link_libraries(${target} PRIVATE
        GTest::gtest_main
        modern-chess-lib
        )

gtest_discover_tests(${target} WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin)