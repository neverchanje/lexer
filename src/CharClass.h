//
// Created by neverchanje on 11/26/15.
//

#ifndef LEXER_CHARCLASS_H
#define LEXER_CHARCLASS_H

#include <bitset>
#include "NFA.h"

namespace lexer {

const size_t CHAR_SIZE = 256;

/**
 * Character class.
 */
class CharClass {
 public:

  CharClass() :
      negated_(false) {
  }

  CharClass(const std::string &set);

  // Add a single character c into a CharClass.
  void Add(char c);

  // Add characters in range of [lb, ub] into CharaClass.
  void AddRange(char lb, char ub);

  // Check if the CharClass contains the character c.
  bool Contains(char c) const;

  // O(1).
  void Negate();

  // Debugging method to write out all of the characters in
  // CharClass.
  void Dump() const;

  NFA::Machine AddToNFA(NFA &nfa, const NFA::Machine &ccl);

 private:

  std::bitset<CHAR_SIZE> charset_;

  bool negated_;

};

} // namespace lexer

#endif //LEXER_CHARCLASS_H
