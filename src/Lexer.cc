//
// Created by neverchanje on 11/29/15.
//

#include "Lexer.h"
#include "CharClass.h"


using namespace lexer;

void Lexer::InitNFA() {
  addDefSect();
  addRuleSect();
  addCodeSect();
}

void Lexer::addDefSect() {

  {
    //---- add rule of NAME into NFA ---
    // NAME <= [_a-zA-Z][a-zA-Z0-9_-]*

    Machine m = nfa_.Mach();

    CharClass nccl1;
    Machine m1(m.start, nfa_.MakeState());
    nccl1.Add('_');
    nccl1.AddRange('a', 'z');
    nccl1.AddRange('A', 'Z');
    nccl1.AddToNFA(nfa_, m1.start, m1.final);

    CharClass nccl2;
    Machine m2(m1.final, nfa_.MakeState());
    nccl2.AddRange('a', 'z');
    nccl2.AddRange('A', 'Z');
    nccl2.AddRange('0', '9');
    nccl2.Add('_');
    nccl2.Add('-');
    nccl2.AddToNFA(nfa_, m2.start, m2.final);
    m2 = nfa_.MakeClosure(m2);
    nfa_.AddAccept(m2.final, TokenID::NAME);
  }

  {
    //---- add rule of WS into NFA ---
    // WS <= [ \t]+

    CharClass ccl(" \t");
    Machine m(NFA::START_STATE, nfa_.MakeState());
    ccl.AddToNFA(nfa_, m.start, m.final);
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
  while (true) {
    c = input_.Read();
    break;
  }
  return true;
}

void Lexer::Gen() {

}

void Lexer::initDFA() {

}
