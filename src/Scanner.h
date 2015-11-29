//
// Created by neverchanje on 11/20/15.
//

#ifndef LEXER_LEXER_H
#define LEXER_LEXER_H

#include <boost/noncopyable.hpp>
#include <iostream>
#include "File.h"

namespace lexer {

class Scanner:  boost::noncopyable {
 public:

  //Use stdin and stdout as default file input stream and output stream.
  Scanner();

  int Scan();

  // The token corresponding to the matched pattern.
  const char *TokenData() const { return token_.data(); }
  size_t TokenLen() const { return token_.length(); }

 private:
  FileInput input_;
  FileOutput output_;
  std::string token_;
};

} //namespace lexer

#endif //LEXER_LEXER_H
