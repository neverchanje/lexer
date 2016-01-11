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
#include "DFA.h"

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
  void Parse(const std::string &s);

  // (DEBUG)
  const NFA &GetNFA() const { return nfa_; }

  // (DEBUG)
  const DFA &GetDFA() const { return dfa_; }

  bool Match(const std::string &s);

 private:

  void parseLiteral(char c);

  void parseCharClass(const char *t);

  void parseVerticalBar();

  void parseStar();

  void parsePlus();

  void parseOpt();

  void parseLeftParen();

  void parseRightParen();

  void doEndJob();

  void doAlternation();

  void doConcatenation();

 private:

  NFA nfa_;
  DFA dfa_;

  std::stack<Regexp> stk_;
};

} // namespace lexer

#endif //LEXER_REGEXP_H
