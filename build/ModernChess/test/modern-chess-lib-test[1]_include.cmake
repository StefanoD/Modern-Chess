if(EXISTS "/Users/stefano/Documents/Programming/C++-Projects/ModernChess/build/ModernChess/test/modern-chess-lib-test[1]_tests.cmake")
  include("/Users/stefano/Documents/Programming/C++-Projects/ModernChess/build/ModernChess/test/modern-chess-lib-test[1]_tests.cmake")
else()
  add_test(modern-chess-lib-test_NOT_BUILT modern-chess-lib-test_NOT_BUILT)
endif()
