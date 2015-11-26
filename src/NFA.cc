//
// Created by neverchanje on 11/25/15.
//

#include "NFA.h"

using namespace lexer;

EpsClosure NFA::GetEpsClosure(const std::vector<State> &T) {
  std::vector<State> S = T;

  EpsClosure E;

  while (!S.empty()) {
    State u = S.back();
    S.pop_back();

    auto &tos = machine_[u][SYM_EPSILON];
    State v;
    for (auto it = tos.begin(); it != tos.end(); it++) {
      v = *it;
      if (E.insert(v).second == true) { // v is not in epsilon closure.
        S.push_back(v);
      }
    }
  }
  return E;
}

void NFA::AddTrans(State from, int sym, State to) {
  machine_[from][sym].push_back(to);
}

void NFA::Dump() {
  for (auto t1 = machine_.begin(); t1 != machine_.end(); t1++) {
    for (auto t2 = (*t1).second.begin(); t2 != machine_.end(); t2++) {
      for (auto t3 = (*t2).second.begin(); t3 != machine_.end(); t3++) {
        fprintf(stderr, "%d: %d, %d\n", t1->first, t2->first, *t3);
      }
    }
  }
}

DFA NFA::ToDFA() const {

}