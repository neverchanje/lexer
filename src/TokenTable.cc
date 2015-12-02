//
// Created by neverchanje on 12/2/15.
//

#include "TokenTable.h"

using namespace lexer;

static const char *TokenTypeStr[] = {
    "NAME",
    "WHITESPACE",
    "NEWLINE"
};

const char *GetTokenType(TokenType type) {
  return TokenTypeStr[type];
}