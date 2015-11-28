
set(LEXER_SRC
        Lexer.h Lexer.cc
        DFA.h DFA.cc
        NFA.h NFA.cc
        SymbolTable.h
        CharClass.h CharClass.cc
        LexerDef.h
        InputBuffer.h InputBuffer.cc
        Rule.h Rule.cc
        FileInput.h FileInput.cc
        )

add_executable(lexer ${LEXER_SRC})
target_link_libraries(lexer ${Boost_LIBRARIES})

include_directories(lib)
add_subdirectory(lib)