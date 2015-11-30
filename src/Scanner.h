//
// Created by neverchanje on 11/20/15.
//

#ifndef LEXER_LEXER_H
#define LEXER_LEXER_H

#include <boost/noncopyable.hpp>
#include <string>
#include "File.h"

namespace lexer {

// Base class of a general scanner.
class Scanner: boost::noncopyable {

 public:

  // Use stdin as default file input stream.
  Scanner() = default;

  virtual int Scan() = 0;

  // The token corresponding to the matched pattern.
  const char *TokenData() const { return token_.data(); }
  size_t TokenLen() const { return token_.length(); }

 protected:
  FileInput input_;
  std::string token_;
};

} //namespace lexer

#endif //LEXER_LEXER_H
