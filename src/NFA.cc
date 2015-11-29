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

    auto &tos = trans1_[u][SYM_EPSILON];
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
  trans1_[from][sym].push_back(to);
  trans2_[from][to] = sym;
}

void NFA::Dump() const {
  fprintf(stderr, "------- Begining of dumping the NFA. -------");
  for (auto t1 = trans1_.begin(); t1 != trans1_.end(); t1++) {
    for (auto t2 = (*t1).second.begin(); t2 != trans1_.end(); t2++) {
      for (auto t3 = (*t2).second.begin(); t3 != trans1_.end(); t3++) {
        fprintf(stderr, "%d: %d, %d\n", t2->first, t1->first, *t3);
      }
    }
  }
  fprintf(stderr, "------- Ending of dumping the NFA. -------\n");
}

DFA NFA::ToDFA() const {

}

State NFA::MakeState() {
  State stateId = maxStateId_;
  maxStateId_++;
  return stateId;
}

Machine NFA::MakeOpt(Machine mach) {
  State start = MakeState();
  State final = MakeState();
  AddTrans(start, SYM_EPSILON, mach.start);
  AddTrans(mach.final, SYM_EPSILON, final);
  AddTrans(start, SYM_EPSILON, final);
  return Machine(start, final);
}

Machine NFA::MakeOr(Machine first, Machine second) {
  State start = MakeState();
  State final = MakeState();
  AddTrans(start, SYM_EPSILON, first.start);
  AddTrans(start, SYM_EPSILON, second.start);
  AddTrans(first.final, SYM_EPSILON, final);
  AddTrans(second.final, SYM_EPSILON, final);
  return Machine(start, final);
}

int NFA::NumOfStates() const {
  return maxStateId_;
}

void NFA::AddAccept(State accept, const AcceptData &data) {
  accepts_[accept] = data;
}

Machine NFA::MakeClosure(Machine mach) {
  return MakeOpt(MakePosClosure(mach));
}

Machine NFA::MakePosClosure(Machine mach) {
  AddTrans(mach.final, SYM_EPSILON, mach.start);
  return mach;
}