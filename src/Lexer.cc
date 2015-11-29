//
// Created by neverchanje on 11/29/15.
//

#include "Lexer.h"

using namespace lexer;

void Lexer::initNFA() {
  addDefSect();
  addRuleSect();
  addCodeSect();
}

void Lexer::addDefSect() {
  //---- add rule of NAME into NFA ---

}
