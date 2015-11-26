//
// Created by neverchanje on 11/24/15.
//

#ifndef LEXER_DFA_H

#include <NFA.h>

namespace lexer {

/**
 * Deterministic Finite Automata
 */
class DFA {

 public:

  static DFA FromNFA(const NFA &nfa) {
    return nfa.ToDFA();
  }

 private:

  // DFA is only allowed to be constructed by a NFA.
  DFA() = default;

  std::vector<State> state_;

};

} // namespace lexer

#endif //LEXER_DFA_H
