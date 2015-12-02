//
// Created by neverchanje on 11/20/15.
//

#ifndef LEXER_SCANNER_H
#define LEXER_SCANNER_H

#include <boost/noncopyable.hpp>
#include <string>
#include "File.h"

namespace lexer {

// Base class of a general scanner.
class Scanner {

 public:

  Scanner() :
      buf_(input_.GetBufferLval()) {
  }

  // Returns false if an eof is hit.
  virtual bool Scan() = 0;

  void SetInputFile(const char *file) { input_.Reset(file); }

  // The token corresponding to the matched pattern.
  const char *TokenData() const { return token_.data(); }
  size_t TokenLen() const { return token_.length(); }

 protected:
  FileInput input_;
  std::string token_;
  Buffer &buf_;
};

} //namespace lexer

#endif //LEXER_SCANNER_H
