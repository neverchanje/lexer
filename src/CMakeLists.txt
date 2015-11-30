
set(LEXER_SRC
        Lexer.h Lexer.cc
        Scanner.h Scanner.cc
        DFA.h DFA.cc
        NFA.h NFA.cc
        SymbolTable.h
        CharClass.h CharClass.cc
        LexerDef.h
#        Rule.h Rule.cc
        File.h
        Generator.h Generator.cc
        main.cc
        )

add_executable(lexer ${LEXER_SRC})
target_link_libraries(lexer ${Boost_LIBRARIES})

include_directories(lib)
add_subdirectory(lib)