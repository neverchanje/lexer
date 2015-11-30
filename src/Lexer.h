//
// Created by neverchanje on 11/29/15.
//

#ifndef LEXER_LEXER_H
#define LEXER_LEXER_H

#include <boost/noncopyable.hpp>
#include "NFA.h"
#include "Scanner.h"
#include "Generator.h"

namespace lexer {

class Lexer: public Scanner,
             public Generator {
 public:

  Lexer() = default;

  bool Scan();

  void Gen();

 private:

  typedef NFA::Machine Machine;

  // Constructing the NFA used in lexer from regular expressions.
  // The details of the conversion can be found in doc/lexer.md.
  void initNFA();
  // Add rules in definition section.
  void addDefSect();
  // Add rules in rule section.
  void addRuleSect();
  // Add rules in code section.
  void addCodeSect();

 private:

  void initDFA();

 private:
  NFA nfa_;
};

} // namespace lexer

#endif //LEXER_LEXER_H
