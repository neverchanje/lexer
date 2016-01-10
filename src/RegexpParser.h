//
// Created by neverchanje on 1/9/16.
//

#ifndef LEXER_REGEXP_H
#define LEXER_REGEXP_H

#include <iosfwd>
#include <memory>
#include <stack>
#include "DisallowCopying.h"
#include "CharClass.h"

namespace lexer {


class RegexpParser {
  __DISALLOW_COPYING__(RegexpParser);

 public:

  enum OpCode {
    NONE,
    LEFT_PAREN,
    ALTERNATE
  };

  struct Regexp {
    NFA::Machine mach;
    OpCode op;

    Regexp(NFA::Machine m, OpCode o) :
        mach(m),
        op(o) {
    }
  };

 public:

  RegexpParser() = default;

  // RegexpParser::Parse returns an NFA constructed by the given regular expression.
  // The construction maintains a stack of Machines,
  // Scanning one of the symbols in star*, plus+, opt? will merge the
  NFA &Parse(const std::string &s);

  void ParseLiteral(char c);

  void ParseCharClass(const char *t);

  void ParseVerticalBar();

  void ParseStar();

  void ParsePlus();

  void ParseOpt();

  void ParseLeftParen();

  void ParseRightParen();

  // (DEBUG)
  const NFA &GetNFA() const { return nfa_; }

  void DoEndJob();

  void DoAlternation();

  void DoConcatenation();

 private:

  NFA nfa_;

  std::stack<Regexp> stk_;
};

} // namespace lexer

#endif //LEXER_REGEXP_H
