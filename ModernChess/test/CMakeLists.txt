set(target modern-chess-lib-test)

add_executable(${target}
        main.cpp
        )

target_link_libraries(${target} PRIVATE
        gtest gtest_main gmock gmock_main
        modern-chess-lib
        )

gtest_discover_tests(${target} WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin)