project(lexer_tests)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_subdirectory(lib/gtest-1.7.0)


set(NFAUnitTest_SRC ${LEXER_SOURCE_DIR}/NFA.cc ${LEXER_SOURCE_DIR}/DFA.cc)
add_executable(NFAUnitTest NFA_unittest.cc ${NFAUnitTest_SRC})
target_link_libraries(NFAUnitTest gtest gtest_main)