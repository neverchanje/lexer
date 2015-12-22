//
// Created by neverchanje on 11/24/15.
//

#ifndef LEXER_DFA_H

#include <unordered_map>
#include "LexerDef.h"

namespace lexer {

/**
 * Deterministic Finite Automaton
 */
class DFA {

 public:

  static const int START_STATE = 0;

  // DFA is created with a start state.
  DFA() :
      start_(START_STATE),
      maxStateId_(1) {
  }

  int NumOfStates() const { return maxStateId_; }

  State MaxStateId() const { return maxStateId_; }

  State MakeState() { return maxStateId_++; }

  void AddTrans(State from, Sym sym, State to);

  bool HasTrans(State from, Sym sym) const;

  State GetTrans(State, Sym sym) const;

  // Debugging method to write out all of the transitions in the DFA.
  void Dump() const;

 private:

  std::unordered_map<State, std::unordered_map<Sym, State> > trans_;

  State start_;

  int maxStateId_;

};

} // namespace lexer

#endif //LEXER_DFA_H
