//
// Created by neverchanje on 11/25/15.
//

#include <cassert>
#include <boost/functional/hash.hpp>
#include "NFA.h"
#include "DFA.h"

using namespace lexer;

typedef NFA::Machine Machine;

// TODO: use a better hasher
struct StateSetHasher {
  size_t operator()(const NFA::StateSet &val) const {
    std::vector<NFA::State> arr(val.begin(), val.end());
    std::sort(arr.begin(), arr.end());
    return boost::hash_value(arr);
  }
};

typedef std::unordered_map<NFA::StateSet, DFA::State, StateSetHasher> StateSetTable;

static const NFA::StateSet &
findInDStates(const StateSetTable &table, DFA::State id) {
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

void NFA::getAllSymsFromT(std::vector<NFA::Sym> &symlist,
                          const NFA::StateSet &T) const {
  symlist.clear();
  for (State st : T) {
    auto found = trans1_.find(st);
    if (found != trans1_.end()) {
      for (const auto &it : (*found).second) {
        if (it.first != SYM_EPSILON)
          symlist.push_back(it.first);
      }
    }
  }
  std::sort(symlist.begin(), symlist.end());
  auto last = std::unique(symlist.begin(), symlist.end());
  symlist.erase(last, symlist.end());
}

DFA NFA::ToDFA() const {
  DFA dfa;
  EpsClosure E;
  std::vector<State> unmarked;
  StateSetTable table;
  State maxID = 0;
  StateSet U;
  std::vector<Sym> symlist;

  GetEpsClosure(std::vector<State>({START_STATE}), E);
  table[E] = maxID;
  unmarked.push_back(maxID++);

  while (!unmarked.empty()) {
    State Tid = unmarked.back();
    unmarked.pop_back();

    const StateSet &T = findInDStates(table, Tid);

    getAllSymsFromT(symlist, T);

    for (auto a : symlist) {
      U.clear();

      // get U
      for (State t : T) {
        auto opt_pvec = GetTrans(t, a);
        if (!opt_pvec) continue;

        const auto &vec = *(*opt_pvec);

        GetEpsClosure(vec, E);
        U.insert(E.begin(), E.end());
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
  if (!E.empty()) E.clear();

  std::vector<State> S = T;

  E.clear();
  // copy initial states into epsilon closure
  for (auto i : S) E.insert(i);

  while (!S.empty()) {
    State u = S.back();
    S.pop_back();

    // Skip if there's no epsilon transition out from u
    auto opt_ptos = GetTrans(u, SYM_EPSILON);
    if (!opt_ptos) continue;

    const auto &tos = *(*opt_ptos);
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

Machine NFA::MakeOpt(const Machine &mach) {
  State start = MakeState();
  State final = MakeState();
  AddTrans(start, SYM_EPSILON, mach.start);
  AddTrans(mach.final, SYM_EPSILON, final);
  AddTrans(start, SYM_EPSILON, final);
  return Machine(start, final);
}

Machine NFA::MakeOr(const Machine &first, const Machine &second) {
// it doesn't make sense to create a self-loop with epsilon.
  if (first.start != second.start)
    AddTrans(first.start, SYM_EPSILON, second.start);
  if (first.final != second.final)
    AddTrans(second.final, SYM_EPSILON, first.final);
  return first;
}

Machine NFA::MakeClosure(const Machine &mach) {
  State start = MakeState();
  State final = MakeState();
  AddTrans(start, SYM_EPSILON, mach.start);
  AddTrans(mach.final, SYM_EPSILON, final);
  AddTrans(final, SYM_EPSILON, start);
  AddTrans(start, SYM_EPSILON, final);
  return Machine(start, final);
}

Machine NFA::MakePosClosure(const Machine &mach) {
  State start = MakeState();
  State final = MakeState();
  AddTrans(start, SYM_EPSILON, mach.start);
  AddTrans(mach.final, SYM_EPSILON, final);
  AddTrans(final, SYM_EPSILON, start);
  return Machine(start, final);
}

boost::optional<const std::vector<NFA::State> *>
NFA::GetTrans(NFA::State from, NFA::Sym sym) const {
  auto found1 = trans1_.find(from);
  if (found1 == trans1_.end())
    return boost::none;

  auto found2 = found1->second.find(sym);
  if (found2 == found1->second.end()) {
    return boost::none;
  }
  return &(found2->second);
}
