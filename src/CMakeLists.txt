
set(LEXER_SRC
        Lexer.h Lexer.cc
        DFA.h DFA.cc
        NFA.h NFA.cc
        SymbolTable.h
        CharClass.h CharClass.cc
        LexerDef.h
)

add_executable(lexer ${LEXER_SRC})
target_link_libraries(lexer ${Boost_LIBRARIES})

add_subdirectory(logger)