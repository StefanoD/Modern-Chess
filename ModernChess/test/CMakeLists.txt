set(target modern-chess-lib-test)

add_executable(${target}
        AttacksGenerationTest.cpp
        BoardTest.cpp
        BitBoardConstantsTest.cpp
        BitBoardOperationsTest.cpp
        MoveGenerationsTest.cpp)

target_link_libraries(${target} PRIVATE
        GTest::gtest_main
        modern-chess-lib
        )

gtest_discover_tests(${target} WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin)