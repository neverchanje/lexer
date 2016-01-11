//
// Created by neverchanje on 11/24/15.
//

#ifndef LEXER_DFA_H
#define LEXER_DFA_H

#include <unordered_map>
#include <unordered_set>
#include <boost/optional/optional.hpp>
#include "DisallowCopying.h"

namespace lexer {

/**
 * Deterministic Finite Automaton
 */
class DFA {

 public:

  typedef int State;

  typedef int SymbolID;

  static const State START_STATE = 0;

  // DFA is created with a start state.
  DFA() :
      maxStateId_(1) {
  }

  int NumOfStates() const { return maxStateId_; }

  State MaxStateId() const { return maxStateId_; }

  State MakeState() { return maxStateId_++; }

  void AddTrans(State from, SymbolID sym, State to);

  bool HasTrans(State from, SymbolID sym) const;

  boost::optional<State> GetTrans(State, SymbolID sym) const;

  inline void AddAccept(State acc) { accepts_.insert(acc); }
  inline bool IsAccept(State st) const { return accepts_.find(st) != accepts_.end(); }

 public:

  // (DEBUG) Write out all of the transitions in the DFA.
  void Dump() const;

  // (DEBUG)
  std::string ToString() const;

  // (DEBUG) Return the internal transition table.
  const std::unordered_map<State, std::unordered_map<SymbolID, State> > &
  GetTransTable() const { return trans_; };

 private:

  std::unordered_map<State, std::unordered_map<SymbolID, State> > trans_;

  std::unordered_set<State> accepts_;

  int maxStateId_;

};

} // namespace lexer

#endif //LEXER_DFA_H
