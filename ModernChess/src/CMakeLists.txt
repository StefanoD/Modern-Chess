set(target modern-chess-lib)

add_library(${target}
        board0x88.cpp
        stdafx.cpp)

target_include_directories(${target} PUBLIC ../include)

