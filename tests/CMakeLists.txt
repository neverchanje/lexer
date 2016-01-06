project(lexer_tests)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_subdirectory(lib/gtest-1.7.0)

add_executable(NFAUnitTest
        NFA_unittest.cc
        ${LEXER_SOURCE_DIR}/NFA.cc
        ${LEXER_SOURCE_DIR}/DFA.cc)
target_link_libraries(NFAUnitTest gtest gtest_main)