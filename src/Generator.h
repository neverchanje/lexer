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

  Generator() = default;

  void SetOutputFile(const char *file) { output_.Reset(file); }

  virtual void Gen() = 0;

 protected:
  FileOutput output_;
};

} //namespace lexer

#endif //LEXER_GENERATOR_H
