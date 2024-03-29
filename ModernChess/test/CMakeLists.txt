set(target modern-chess-lib-test)

add_executable(${target}
        AttackQueriesTest.cpp
        BoardHelperUtility.h
        BasicParserTest.cpp
        BishopAttacksTest.cpp
        BitBoardConstantsTest.cpp
        BitBoardOperationsTest.cpp
        BoardTest.cpp
        FenParsingTest.cpp
        EvaluationTest.cpp
        GameStateTest.cpp
        MagicNumberCandidatesGeneration.cpp
        PawnAttacksTest.cpp
        PawnPushesTest.cpp
        QueenAttacksTest.cpp
        PawnQueriesTest.cpp
        RookAttacksTest.cpp
        SquareTest.cpp
        MoveTest.cpp
        PseudoMoveGenerationTest.cpp
        UtilitiesTest.cpp
        CastlingRightsTest.cpp
        MoveExecutionTest.cpp
        TestingPositions.h
        PerftTest.cpp
        UCIParserTest.cpp
        UCICommunicationTest.cpp
        ZobristHasherTest.cpp)

target_link_libraries(${target} PRIVATE
        GTest::gtest_main
        modern-chess-lib
        perft-lib
        )

gtest_discover_tests(${target} WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin)