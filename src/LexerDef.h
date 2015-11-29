//
// Created by neverchanje on 11/27/15.
//

#ifndef LEXER_LEXERDEF_H
#define LEXER_LEXERDEF_H

#include <functional>

namespace lexer {

const size_t CHAR_SIZE = 256;

typedef int State;

struct AcceptData {
  std::string Token;
  std::function<void()> Action;
};

} // namespace lexer

#endif //LEXER_LEXERDEF_H
