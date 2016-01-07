//
// Created by neverchanje on 12/2/15.
//

#include "TokenTable.h"

namespace lexer {

static const char *TokenIDStr[] = {
    "NAME",
    "WS",
    "OPTWS",
    "NEWLINE"
};

const char *GetToken(TokenID type) {
  return TokenIDStr[type];
}

} // naemspace lexer