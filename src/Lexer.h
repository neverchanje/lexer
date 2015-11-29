//
// Created by neverchanje on 11/29/15.
//

#ifndef LEXER_LEXER_H
#define LEXER_LEXER_H

#include <boost/noncopyable.hpp>
#include <NFA.h>

namespace lexer {

class Lexer: boost::noncopyable {
 public:
 private:
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
  void genTable();
 private:
  NFA nfa_;
};

} // namespace lexer

#endif //LEXER_LEXER_H
