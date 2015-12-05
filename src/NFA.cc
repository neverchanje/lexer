//
// Created by neverchanje on 11/25/15.
//

#include <cassert>
#include <boost/functional/hash.hpp>
#include "NFA.h"
#include "DFA.h"

using namespace lexer;

// cannot be deleted
typedef NFA::Machine Machine;

struct StateSetHasher {
  size_t operator()(const StateSet &val) const {
    return boost::hash_range(val.begin(), val.end());
  }
};

typedef std::unordered_map<StateSet, State, StateSetHasher> StateSetTable;

static const StateSet &findInDStates(const StateSetTable &table, State id) {
  bool found = false;
  for (auto it = table.begin(); it != table.end(); it++) {
    if (it->second == id) {
      found = true;
      return it->first;
    }
  }
  assert(found);
  return table.begin()->first;
}

#define SKIP_IF_NO_TRANSITION(from, sym) \
{ \
  const auto &t1 = trans1_.find(from); \
  if (t1 == trans1_.end()) continue; \
  const auto &t2 = t1->second.find(sym); \
  if (t2 == t1->second.end()) continue; \
}

DFA NFA::ToDFA() {
  DFA dfa;
  EpsClosure E;

  std::vector<State> unmarked;
  StateSetTable table;
  State maxID = 0;
  StateSet U;
  std::vector<Sym> symlist;

  GetEpsClosure(std::vector<State>({start_}), E);
  table[E] = maxID;
  unmarked.push_back(maxID++);

  while (!unmarked.empty()) {
    State Tid = unmarked.back();
    unmarked.pop_back();

    const StateSet &T = findInDStates(table, Tid);

    // get all symbols out from T
    symlist.clear();
    for (auto st : T) {
      Sym a = trans1_.find(st)->first;
      if (a != SYM_EPSILON) {
        symlist.push_back(a);
      }
    }

    for (auto a : symlist) {
      E.clear();
      U.clear();

      // get U
      for (auto t : T) {
        SKIP_IF_NO_TRANSITION(t, a);
        const auto &vec = GetTrans(t, a);

        GetEpsClosure(vec, E);
        U.insert(vec.begin(), vec.end());
      }

      // if U is not in DStates
      auto it = table.find(U);
      State Uid;
      if (it == table.end()) {
        table[U] = Uid = maxID;
        unmarked.push_back(maxID++);
      } else {
        Uid = it->second;
      }

      dfa.AddTrans(Tid, a, Uid);
    }
  }
  return dfa;
}

void NFA::GetEpsClosure(const std::vector<State> &T, EpsClosure &E) const {
  // Since retrieving from unordered_map requires modification of the map,
  // this method cannot be marked const.
  std::vector<State> S = T;

  E.clear();
  // copy initial states into epsilon closure
  for (auto i : S) E.insert(i);

  while (!S.empty()) {
    State u = S.back();
    S.pop_back();

    // if there's no epsilon transition out from u
    SKIP_IF_NO_TRANSITION(u, SYM_EPSILON);
    const auto &tos = GetTrans(u, SYM_EPSILON);
    for (State v : tos) {
      if (E.insert(v).second == true) { // v is not in epsilon closure.
        S.push_back(v);
      }
    }
  }
}

void NFA::AddTrans(State from, Sym sym, State to) {
  trans1_[from][sym].push_back(to);
  trans2_[from][to] = sym;
}

void NFA::Dump() const {
  fprintf(stderr, "\n------- Begining of dumping the NFA. -------\n");
  for (auto t1 = trans2_.begin(); t1 != trans2_.end(); t1++) {
    for (auto t2 = (*t1).second.begin(); t2 != (*t1).second.end(); t2++) {
      fprintf(stderr, "<from:%d, sym:%d, to:%d>\n",
              (*t1).first, (*t2).second, (*t2).first);
    }
  }
  fprintf(stderr, "------- Ending of dumping the NFA. -------\n");
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

void NFA::AddAccept(State accept, int data) {
  AddTrans(accept, SYM_EPSILON, final_);
  accepts_[accept] = data;
}

Machine NFA::MakeClosure(Machine mach) {
  return MakeOpt(MakePosClosure(mach));
}

Machine NFA::MakePosClosure(Machine mach) {
  AddTrans(mach.final, SYM_EPSILON, mach.start);
  return mach;
}

bool NFA::FindTrans(State from, Sym sym) const {
  if (trans1_.find(from) == trans1_.end()) {
    return false;
  }
  auto &t1 = trans1_.find(from)->second;
  return (t1.find(sym) != t1.end());
}

const std::vector<State> &NFA::GetTrans(State from, Sym sym) const {
  return trans1_.find(from)->second.find(sym)->second;
}