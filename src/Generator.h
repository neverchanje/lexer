//
// Created by neverchanje on 11/28/15.
//

#ifndef LEXER_GENERATOR_H
#define LEXER_GENERATOR_H

#include "File.h"

namespace lexer {

// Base class of a general generator.
class Generator {

 public:

  // Use stdout as default file output stream.
  Generator() = default;

  virtual void Gen() = 0;

 protected:
  FileOutput output_;
  Buffer &buf_;
};

} //namespace lexer

#endif //LEXER_GENERATOR_H
