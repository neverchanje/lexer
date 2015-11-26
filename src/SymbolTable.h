//
// Created by neverchanje on 11/25/15.
//

#ifndef LEXER_SYMBOLTABLE_H
#define LEXER_SYMBOLTABLE_H

#include <unordered_map>
#include <string>

typedef std::string Sym;

struct Def {
  std::string str_def;
  int int_def;
};

typedef std::unordered_map<Sym, Def> SymbolTable;

#endif //LEXER_SYMBOLTABLE_H
