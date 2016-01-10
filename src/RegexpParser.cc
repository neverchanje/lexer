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

  DoEndJob();
  return nfa_;
}

void RegexpParser::ParseLiteral(char c) {
  NFA::Machine m(nfa_.MakeState(), nfa_.MakeState());
  nfa_.AddTrans(m.start, c, m.final);
  stk_.push(Regexp(m, OpCode::NONE));
}

void RegexpParser::ParseCharClass(const char *t) {
  CharClass ccl;
  for (; (*t) != ']' && (*t) != '\0'; t++) {
    ccl.Add(*t);
  }
  assert((*t) != '\0');

  NFA::Machine m(nfa_.MakeState(), nfa_.MakeState());
  ccl.AddToNFA(nfa_, m);
  stk_.push(Regexp(m, OpCode::NONE));
}

// this algorithm doesn't take adjacent vertical bars "||" in to consideration.
void RegexpParser::ParseVerticalBar() {

  stk_.push(Regexp(NFA::Machine(), OpCode::ALTERNATE));
}

void RegexpParser::ParseStar() {
  assert(!stk_.empty());
  NFA::Machine m = stk_.top().mach;
  stk_.pop();
  m = nfa_.MakeClosure(m);
  stk_.push(Regexp(m, OpCode::NONE));
}

void RegexpParser::ParsePlus() {
  assert(!stk_.empty());
  NFA::Machine m = stk_.top().mach;
  stk_.pop();
  m = nfa_.MakePosClosure(m);
  stk_.push(Regexp(m, OpCode::NONE));
}

void RegexpParser::ParseOpt() {
  assert(!stk_.empty());
  NFA::Machine m = stk_.top().mach;
  stk_.pop();
  m = nfa_.MakeOpt(m);
  stk_.push(Regexp(m, OpCode::NONE));
}

void RegexpParser::ParseLeftParen() {
  stk_.push(Regexp(NFA::Machine(), OpCode::LEFT_PAREN));
}

// When a right parenthesis is hit, the stack must be in the form of
// ... LeftParen Regex VerticalBar Regex VerticalBar ... Regex, or only
// a LeftParen.
void RegexpParser::ParseRightParen() {
  DoConcatenation();
  DoAlternation();
}

void RegexpParser::DoEndJob() {
  DoConcatenation();
  DoAlternation();
  nfa_.AddTrans(nfa_.START_STATE, NFA::SYM_EPSILON, stk_.top().mach.start);
}

void RegexpParser::DoAlternation() {
  if (stk_.empty()) {
    return;
  }
  OpCode op;
  NFA::Machine m = stk_.top().mach;
  stk_.pop();
  while (!stk_.empty()) {
    op = stk_.top().op;
    if (op == OpCode::LEFT_PAREN) {
      stk_.pop();
      break;
    }
    if (op == OpCode::ALTERNATE) {
      stk_.pop();
      assert(!stk_.empty());
      m = nfa_.MakeOr(m, stk_.top().mach);
    }
    else {
      assert(op != OpCode::NONE);
    }
    stk_.pop();
  }
  stk_.push(Regexp(m, OpCode::NONE));
}

void RegexpParser::DoConcatenation() {
  if (stk_.empty()) {
    return;
  }
  NFA::Machine m = stk_.top().mach;
  OpCode op;
  stk_.pop();

  // do concatenation
  while (!stk_.empty()) {
    op = stk_.top().op;
    if (op == OpCode::ALTERNATE || op == OpCode::LEFT_PAREN) {
      break;
    }
    nfa_.AddTrans(stk_.top().mach.final, NFA::SYM_EPSILON, m.start);
    m.start = stk_.top().mach.start;
    stk_.pop();
  }
  stk_.push(Regexp(m, OpCode::NONE));
}

} // namespace lexer