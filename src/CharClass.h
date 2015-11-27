//
// Created by neverchanje on 11/26/15.
//

#ifndef LEXER_CHARCLASS_H
#define LEXER_CHARCLASS_H

#include <bitset>

#include "LexerDef.h"

namespace lexer {

/**
 * Character class.
 */
class CharClass {
 public:

  CharClass() :
      negated_(false) {
  }

  // Add a single character c to a CharClass.
  void Add(char c);

  // Check if the CharClass contains the character c.
  bool Contains(char c) const;

  // O(1).
  void Negate();

  // Debugging method to write out all of the characters in
  // CharClass.
  void Dump() const;

 private:

  std::bitset<CHAR_SIZE> charset_;

  bool negated_;

};

} // namespace lexer

#endif //LEXER_CHARCLASS_H
