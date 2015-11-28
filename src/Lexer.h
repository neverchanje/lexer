//
// Created by neverchanje on 11/20/15.
//

#ifndef LEXER_LEXER_H
#define LEXER_LEXER_H

#include <boost/noncopyable.hpp>
#include <iostream>
#include "FileInput.h"

namespace lexer {

// Interface of a general scanner.
class ILexer: boost::noncopyable {
 public:

  virtual int Scan() = 0;

  // The token corresponding to the matched pattern.
  const char *TokenData() const { return token_.data(); }
  size_t TokenLen() const { return token_.length(); }

 protected:
  std::string token_;
};

class Lexer: public ILexer {
 public:

  //Use stdin and stdout as default file input stream and output stream.
  Lexer();

  int Scan();

  void AddDefinition();

  void AddRule();

  void AddUserCodes();

 private:
  FileInput input;
  FileOutput output;
};

} //namespace lexer

#endif //LEXER_LEXER_H
