//
// Created by neverchanje on 1/9/16.
//

#include <string>
#include <stack>
#include "RegexpParser.h"

namespace lexer {

using std::unique_ptr;
using std::stack;

// RegexpParser::Parse is not support associativity currently, which will be done later.
NFA &RegexpParser::Parse(const std::string &s) {

  for (size_t t = 0; t < s.length(); t++) {
    char c = s[t];
    switch (c) {
      case '[': {
        ParseCharClass(s.data() + t);
        break;
      }
      case '(': {
        ParseLeftParen();
        break;
      }
      case ')': {
        ParseRightParen();
        break;
      }
      case '|': {
        ParseVerticalBar();
        break;
      }
      case '*': {
        ParseStar();
        break;
      }
      case '+': {
        ParsePlus();
        break;
      }
      case '?': {
        ParseOpt();
        break;
      }
      default: {
        // literal character
        ParseLiteral(c);
        break;
      }
    }
  }

  return nfa_;
}

#define INIT_REGEXP_MACH(m) m = (!stk_.empty() && stk_.top().op == OpCode::NONE) ? \
  NFA::Machine(stk_.top().mach.final, nfa_.MakeState()) : \
  NFA::Machine(nfa_.MakeState(), nfa_.MakeState())

void RegexpParser::ParseLiteral(char c) {
  NFA::Machine m;
  INIT_REGEXP_MACH(m);
  nfa_.AddTrans(m.start, c, m.final);
  stk_.push(Regexp(m, OpCode::NONE));
}

void RegexpParser::ParseCharClass(const char *t) {
  CharClass ccl;
  for (; (*t) != ']' && (*t) != '\0'; t++) {
    ccl.Add(*t);
  }
  assert((*t) != '\0');

  NFA::Machine m;
  INIT_REGEXP_MACH(m);

  ccl.AddToNFA(nfa_, m);
  stk_.push(Regexp(m, OpCode::NONE));
}

// this algorithm doesn't take adjacent vertical bars "||" in to consideration.
void RegexpParser::ParseVerticalBar() {
  NFA::Machine m = stk_.top().mach;
  OpCode op;

  // do concatenation
  while (!stk_.empty()) {
    op = stk_.top().op;
    if (op == OpCode::ALTERNATE || op == OpCode::LEFT_PAREN) {
      break;
    }
    m.start = stk_.top().mach.start;
    stk_.pop();
  }
  stk_.push(Regexp(m, OpCode::NONE));

  stk_.push(Regexp(NFA::Machine(), OpCode::ALTERNATE));
}

void RegexpParser::ParseStar() {
  assert(!stk_.empty());
  NFA::Machine m = stk_.top().mach;
  stk_.pop();
  nfa_.MakeClosure(m);
  stk_.push(Regexp(m, OpCode::NONE));
}

void RegexpParser::ParsePlus() {
  assert(!stk_.empty());
  NFA::Machine m = stk_.top().mach;
  stk_.pop();
  nfa_.MakePosClosure(m);
  stk_.push(Regexp(m, OpCode::NONE));
}

void RegexpParser::ParseOpt() {
  assert(!stk_.empty());
  NFA::Machine m = stk_.top().mach;
  stk_.pop();
  nfa_.MakeOpt(m);
  stk_.push(Regexp(m, OpCode::NONE));
}

void RegexpParser::ParseLeftParen() {
  stk_.push(Regexp(NFA::Machine(), OpCode::LEFT_PAREN));
}

// When a right parenthesis is hit, the stack must be in the form of
// ... LeftParen Regex VerticalBar Regex VerticalBar ... Regex, or only
// a LeftParen.
void RegexpParser::ParseRightParen() {
  OpCode op;
  NFA::Machine m = stk_.top().mach;

  while (!stk_.empty()) {
    op = stk_.top().op;
    if (op == OpCode::LEFT_PAREN) {
      stk_.pop();
      break;
    }
    else if (op == OpCode::ALTERNATE) {
      stk_.pop();
      assert(!stk_.empty());
      nfa_.MakeOr(m, stk_.top().mach);
    }
    assert(op != OpCode::NONE);
    stk_.pop();
  }
}

} // namespace lexer