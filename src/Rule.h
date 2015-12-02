//
// Created by neverchanje on 11/28/15.
//

#ifndef LEXER_RULE_H
#define LEXER_RULE_H

#include "LexerDef.h"
#include "NFA.h"
#include "Block.h"

namespace lexer {

struct Pattern {
  NFA::Machine mach;
  std::string name;
  bool bol; // begin of line

};

class Rule {
 public:

  class Action: public Block {

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
