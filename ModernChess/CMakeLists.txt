project(modern-chess-lib
        VERSION ${VERSION}
        )

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(test_integration)