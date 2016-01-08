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

#define ADD_RANGE_TO_NFA_AS_TOKEN(lb, ub, token) \
{ \
  Machine m(nfa_.START_STATE, nfa_.MakeState()); \
  CharClass ccl; \
  ccl.AddRange(lb, ub); \
  ccl.AddToNFA(nfa_, m); \
  nfa_.AddAccept(m.final, TokenID::token); \
}

void Lexer::addDefSect() {

  //---- add rule of LOWER_CASE_LETTER into NFA ---
  // LOWER_CASE_LETTER <= [a-z]
  ADD_RANGE_TO_NFA_AS_TOKEN('a', 'z', LOWER_CASE_LETTER);

  //---- add rule of UPPER_CASE_LETTER into NFA ---
  // UPPER_CASE_LETTER <= [A-Z]
  ADD_RANGE_TO_NFA_AS_TOKEN('A', 'Z', UPPER_CASE_LETTER);

  //---- add rule of DIGIT into NFA ---
  // DIGIT <= [0-9]
  ADD_RANGE_TO_NFA_AS_TOKEN('0', '9', DIGIT);

  {
    //---- add rule of NAME into NFA ---
    // NAME <= [_a-zA-Z][a-zA-Z0-9_-]*

    Machine m(nfa_.START_STATE, nfa_.MakeState());

    CharClass nccl1;
    Machine m1(m.start, nfa_.MakeState());
    nccl1.Add('_');
    nccl1.AddRange('a', 'z');
    nccl1.AddRange('A', 'Z');
    nccl1.AddToNFA(nfa_, m1);

    CharClass nccl2;
    Machine m2(m1.final, nfa_.MakeState());
    nccl2.AddRange('a', 'z');
    nccl2.AddRange('A', 'Z');
    nccl2.AddRange('0', '9');
    nccl2.Add('_');
    nccl2.Add('-');
    nccl2.AddToNFA(nfa_, m2);
    m2 = nfa_.MakeClosure(m2);
    nfa_.AddAccept(m2.final, TokenID::NAME);
  }

  {
    //---- add rule of WS into NFA ---
    // WS <= [ \t]+

    CharClass ccl(" \t");
    Machine m(NFA::START_STATE, nfa_.MakeState());
    ccl.AddToNFA(nfa_, m);
    m = nfa_.MakePosClosure(m);
    nfa_.AddAccept(m.final, TokenID::WS);

    //---- add rule of OPTWS into NFA ---
    // OPTWS <= WS?

    m = nfa_.MakeClosure(m);
    nfa_.AddAccept(m.final, TokenID::OPTWS);
  }

  {
    //---- add rule of NEWLINE into NFA ---
    // NEWLINE <= \r?\n

    Machine m(NFA::START_STATE, nfa_.MakeState());
    nfa_.AddTrans(m.start, '\n', m.final);
    m = nfa_.MakeOpt(m);
    nfa_.AddAccept(m.final, TokenID::NEWLINE);
  }
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

#undef ADD_RANGE_TO_NFA_AS_TOKEN

} // namespace lexer