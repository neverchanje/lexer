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

    auto &tos = trans_[u][SYM_EPSILON];
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
  trans_[from][sym].push_back(to);
}

void NFA::Dump() const {
  fprintf(stderr, "------- Begining of dumping the NFA. -------");
  for (auto t1 = trans_.begin(); t1 != trans_.end(); t1++) {
    for (auto t2 = (*t1).second.begin(); t2 != trans_.end(); t2++) {
      for (auto t3 = (*t2).second.begin(); t3 != trans_.end(); t3++) {
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
//
//Machine NFA::MakeBranch(Machine first, Machine second) {
////  State mach = MakeState();
////  AddTrans(mach, SYM_EPSILON, first.start);
////  AddTrans(mach, SYM_EPSILON, second.start);
//}
//
//Machine NFA::MakeClosure(Machine mach) {
//  // AddTrans(mach, SYM_EPSILON, mach);
//  // return mach;
//  return MakeOpt(MakePosClosure(mach));
//}
//

//TODO: Optimization.
Machine NFA::MakeOpt(Machine mach) {
  State start = MakeState();
  State final = MakeState();
  AddTrans(start, SYM_EPSILON, mach.start);
  AddTrans(mach.final, SYM_EPSILON, final);
  AddTrans(start, SYM_EPSILON, final);
  return Machine(start, final);
}

//State NFA::MakeOr(Machine first, Machine second) {
//  return 0;
//}
//
//State NFA::MakePosClosure(Machine mach) {
//  return 0;
//}
//
//State NFA::MakeRep(int lb, int ub) {
//  return 0;
//}
//

int NFA::NumOfStates() const {
  return maxStateId_;
}

void NFA::AddAccept(State accept) {
  accepts_.push_back(accept);
}

Machine NFA::MakeClosure(Machine mach) {
  return MakeOpt(MakePosClosure(mach));
}

Machine NFA::MakePosClosure(Machine mach) {
  AddTrans(mach.final, SYM_EPSILON, mach.start);
  return mach;
}
