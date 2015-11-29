//
// Created by neverchanje on 11/28/15.
//

#ifndef LEXER_BLOCK_H
#define LEXER_BLOCK_H

#include <string>

/**
 *
 */
class Block {

  Block() :
      indent_(0) {
  }

  void IndentUp() { indent_++; }
  void IndentDown() { indent_--; }
  int IndentLevel() { return indent_; }

 private:
  int indent_;
};

#endif //LEXER_BLOCK_H
