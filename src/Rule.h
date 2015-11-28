//
// Created by neverchanje on 11/28/15.
//

#ifndef LEXER_RULE_H
#define LEXER_RULE_H

#include "LexerDef.h"
#include "NFA.h"

namespace lexer {

struct Pattern {
  NFA::Machine mach;
  bool bol;
  size_t length; //length of the text matched by this pattern.
};

class Rule {
 public:

  class Action {

  };

 public:

  Rule() {

  }

 private:
  Pattern pattern_;
  Action action_;
};

} // namespace lexer

#endif //LEXER_RULE_H
