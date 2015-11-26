//
// Created by neverchanje on 11/25/15.
//

#ifndef LEXER_NFA_H
#define LEXER_NFA_H

#include <set>
#include <vector>
#include <unordered_map>

namespace lexer {

typedef int State;

/**
 * Definition of epsilon closure in flex:
 * The epsilon closure is the set of all states reachable by an arbitrary
 * number of epsilon transitions, which themselves do not have epsilon
 * transitions going out, unioned with the set of states which have non-null
 * accepting numbers.
 * Since find and insert are the most usual operations in the manipulation
 * of EpsClosure, we use std::set, which is time-efficient in both two.
 */
typedef std::set<State> EpsClosure;

/**
 * Mark the symbol epsilon.
 */
const int SYM_EPSILON = 257;

class DFA;

/**
 * Non-deterministic Finite Automata
 */
class NFA {

 public:

  // Construct the epsilon closure of the set of NFA states T, and return the
  // result.
  // Use Named-Return-Value-Optimization to reduce the copy times.
  EpsClosure GetEpsClosure(const std::vector<State> &T);

  // Subset construction algorithm.
  // We temporarily assume that this method will not modify the internal structure
  // of the NFA.
  DFA ToDFA() const;

  void AddTrans(State from, int sym, State to);

  void Dump(State start);

 private:

  // Transition tuple (State from, int symbol, State to)
  std::unordered_map<State, std::vector<int, State> >machine_;

  std::vector<State> accepts_;

};

} // namespace lexer

#endif //LEXER_NFA_H
