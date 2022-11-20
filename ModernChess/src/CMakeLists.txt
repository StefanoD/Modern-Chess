set(target modern-chess-lib)

add_library(${target}
        attacks.cpp
        book.cpp
        board0x88.cpp
        chronos.cpp
        com.cpp
        console_ui.cpp
        CPW.cpp
        eval.cpp
        eval_init.cpp
        move.cpp
        movegen.cpp
        Quiescence.cpp
        recognizer.cpp
        search.cpp
        see.cpp
        stdafx.cpp
        transposition.cpp
        util.cpp)

target_include_directories(${target} PUBLIC ../include)

