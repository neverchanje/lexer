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

  //Equivalent with nfa.toDFA()
  static DFA FromNFA(const NFA &nfa) {
    return nfa.ToDFA();
  }

 private:

  DFA() = default;

  std::vector<State> state_;

};

} // namespace lexer

#endif //LEXER_DFA_H
