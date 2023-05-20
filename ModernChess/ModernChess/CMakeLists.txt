set(target modern-chess)

add_executable(${target}
        main.cpp
        )

target_link_libraries(${target} PRIVATE
        modern-chess-lib
        )