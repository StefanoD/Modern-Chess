set(target modern-chess-lib-test)

add_executable(${target}
        BoardTest.cpp
        BitBoardConstantsTest.cpp
        BitBoardOperationsTest.cpp
        )

target_link_libraries(${target} PRIVATE
        GTest::gtest_main
        modern-chess-lib
        )

gtest_discover_tests(${target} WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin)