
set(LEXER_SRC
        Lexer.cc
        DFA.cc
        NFA.cc
        TokenTable.cc
        CharClass.cc
        File.cc
        Scanner.h
        Generator.h
        main.cc
        DisallowCopying.h
        )

add_executable(lexer ${LEXER_SRC})
target_link_libraries(lexer ${Boost_LIBRARIES})