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
void RegexpParser::Parse(const std::string &s) {

  for (size_t t = 0; t < s.length(); t++) {
    char c = s[t];
    switch (c) {
      case '[': {
        parseCharClass(s.data() + t);
        break;
      }
      case '(': {
        parseLeftParen();
        break;
      }
      case ')': {
        parseRightParen();
        break;
      }
      case '|': {
        parseVerticalBar();
        break;
      }
      case '*': {
        parseStar();
        break;
      }
      case '+': {
        parsePlus();
        break;
      }
      case '?': {
        parseOpt();
        break;
      }
      default: {
        // literal character
        parseLiteral(c);
        break;
      }
    }
  }

  doEndJob();
  dfa_ = nfa_.ToDFA();
}

void RegexpParser::parseLiteral(char c) {
  NFA::Machine m(nfa_.MakeState(), nfa_.MakeState());
  nfa_.AddTrans(m.start, c, m.final);
  stk_.push(Regexp(m, OpCode::NONE));
}

void RegexpParser::parseCharClass(const char *t) {
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
void RegexpParser::parseVerticalBar() {

  stk_.push(Regexp(NFA::Machine(), OpCode::ALTERNATE));
}

void RegexpParser::parseStar() {
  assert(!stk_.empty());
  NFA::Machine m = stk_.top().mach;
  stk_.pop();
  m = nfa_.MakeClosure(m);
  stk_.push(Regexp(m, OpCode::NONE));
}

void RegexpParser::parsePlus() {
  assert(!stk_.empty());
  NFA::Machine m = stk_.top().mach;
  stk_.pop();
  m = nfa_.MakePosClosure(m);
  stk_.push(Regexp(m, OpCode::NONE));
}

void RegexpParser::parseOpt() {
  assert(!stk_.empty());
  NFA::Machine m = stk_.top().mach;
  stk_.pop();
  m = nfa_.MakeOpt(m);
  stk_.push(Regexp(m, OpCode::NONE));
}

void RegexpParser::parseLeftParen() {
  stk_.push(Regexp(NFA::Machine(), OpCode::LEFT_PAREN));
}

// When a right parenthesis is hit, the stack must be in the form of
// ... LeftParen Regex VerticalBar Regex VerticalBar ... Regex, or only
// a LeftParen.
void RegexpParser::parseRightParen() {
  doConcatenation();
  doAlternation();
}

void RegexpParser::doEndJob() {
  doConcatenation();
  doAlternation();
  nfa_.AddTrans(nfa_.START_STATE, NFA::SYM_EPSILON, stk_.top().mach.start);
  nfa_.AddTrans(stk_.top().mach.final, NFA::SYM_EPSILON, nfa_.FINAL_STATE);
}

void RegexpParser::doAlternation() {
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

void RegexpParser::doConcatenation() {
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

bool RegexpParser::Match(const std::string &s) {
  DFA::State st = DFA::START_STATE;
  for (char c : s) {
    auto optTo = dfa_.GetTrans(st, c);
    if (!optTo)
      return false;
    st = (*optTo);
  }
  return dfa_.IsAccept(st);
}

} // namespace lexer