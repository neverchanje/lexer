//
// Created by neverchanje on 11/24/15.
//

#ifndef LEXER_DFA_H

#include <unordered_map>
#include "LexerDef.h"

namespace lexer {

class NFA;

/**
 * Deterministic Finite Automata
 */
class DFA {

  friend class NFA;

 public:

  static DFA FromNFA(NFA &nfa);

  int NumOfStates() const { return maxStateId_; }

  State MaxStateId() const { return maxStateId_; }

  State MakeState() { return maxStateId_++; }

  void AddTrans(State from, Sym sym, State to);

  bool FindTrans(State from, Sym sym) const;

  State GetTrans(State, Sym sym) const;

  State Start() const { return start_; }

  // Debugging method to write out all of the transitions in the NFA.
  void Dump() const;

 private:

  // DFA is only allowed to be constructed by an NFA.
  DFA() :
      start_(0),
      maxStateId_(1) {
  }

  std::unordered_map<State, std::unordered_map<Sym, State> > trans_;

  State start_;

  int maxStateId_;

};

} // namespace lexer

#endif //LEXER_DFA_H
