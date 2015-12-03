//
// Created by neverchanje on 12/2/15.
//

#include "TokenTable.h"

using namespace lexer;

static const char *TokenIDStr[] = {
    "NAME",
    "WS",
    "OPTWS"
    "NEWLINE"
};

const char *GetTokenID(TokenID type) {
  return TokenIDStr[type];
}