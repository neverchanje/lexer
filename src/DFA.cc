//
// Created by neverchanje on 11/24/15.
//

#include "DFA.h"
#include "NFA.h"

using namespace lexer;

DFA DFA::FromNFA(NFA &nfa) {
  return nfa.ToDFA();
}

void DFA::AddTrans(State from, Sym sym, State to) {
  trans_[from][sym] = to;
}

bool DFA::FindTrans(State from, Sym sym) const {
  if (trans_.find(from) == trans_.end()) {
    return false;
  }
  auto &t1 = trans_.find(from)->second;
  return (t1.find(sym) != t1.end());
}

State DFA::GetTrans(State from, Sym sym) const {
  return trans_.find(from)->second.find(sym)->second;
}

void DFA::Dump() const {
  fprintf(stderr, "\n------- Begining of dumping the DFA. -------\n");
  for (auto t1 = trans_.begin(); t1 != trans_.end(); t1++) {
    for (auto t2 = (*t1).second.begin(); t2 != (*t1).second.end(); t2++) {
      fprintf(stderr, "<from:%d, sym:%d, to:%d>\n",
              (*t1).first, (*t2).first, (*t2).second);
    }
  }
  fprintf(stderr, "------- Ending of dumping the DFA. -------\n");
}
