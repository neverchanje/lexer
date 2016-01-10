//
// Created by neverchanje on 11/29/15.
//

#include "Lexer.h"
#include "CharClass.h"

namespace lexer {

void Lexer::InitNFA() {
  addDefSect();
  addRuleSect();
  addCodeSect();
}

void Lexer::addDefSect() {

}

void Lexer::addRuleSect() {

}

void Lexer::addCodeSect() {

}

bool Lexer::Scan() {
  char c;
  while ((c = input_.Read()) != EOF) {
    printf("%c", c);
  }
  return true;
}

void Lexer::Gen() {

}

void Lexer::initDFA() {

}

} // namespace lexer