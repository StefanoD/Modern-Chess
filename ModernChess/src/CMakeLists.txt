set(target modern-chess-lib)


add_library(${target}
        stdafx.cpp)

target_include_directories(${target} PUBLIC ../include)

