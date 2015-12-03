//
// Created by neverchanje on 11/28/15.
//

#ifndef LEXER_RULE_H
#define LEXER_RULE_H

#include "LexerDef.h"
#include "NFA.h"
#include "Block.h"

namespace lexer {

typedef int PatternID;

int NewPatternID();

/**
 * Example:
 * ActionTable[PATTERN_2] = [](){ do nothing }
 */
typedef std::function<void()> ActionFunc;
typedef std::unordered_map<PatternID, ActionFunc> ActionTable;

struct Pattern {
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
