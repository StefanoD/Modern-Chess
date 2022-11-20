set(target modern-chess-lib-test)

add_executable(${target}
        main.cpp
        )

target_link_libraries(${target} PRIVATE
        GTest::GTest
        modern-chess-lib
        )

gtest_discover_tests(${target} WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin)