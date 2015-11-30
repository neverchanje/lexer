//
// Created by neverchanje on 11/29/15.
//

#include "Lexer.h"
#include "CharClass.h"

using namespace lexer;

void Lexer::initNFA() {
  addDefSect();
  addRuleSect();
  addCodeSect();
}

void Lexer::addDefSect() {
  //---- add rule of NAME into NFA ---
  // NAME <= [_a-zA-Z][a-zA-Z0-9_-]*

  Machine m = nfa_.Machine();
  State mid = nfa_.MakeState();

  CharClass nccl1;
  nccl1.Add('_');
  nccl1.AddRange('a', 'z');
  nccl1.AddRange('A', 'Z');
  nccl1.AddToNFA(nfa_, m.Start, mid);

  CharClass nccl2;
  nccl2.AddRange('a', 'z');
  nccl2.AddRange('A', 'Z');
  nccl2.AddRange('0', '9');
  nccl2.Add('_');
  nccl2.Add('-');
  nccl2.AddToNFA(nfa_, mid, m.Final);
  nfa_.MakeClosure(Machine(mid, m.Final));
}

void Lexer::addRuleSect() {

}

void Lexer::addCodeSect() {

}
