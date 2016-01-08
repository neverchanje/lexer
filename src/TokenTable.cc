//
// Created by neverchanje on 12/2/15.
//

#include "TokenTable.h"
#include "NFA.h"

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

NFA::Machine ToMachine(NFA &nfa, TokenID token) {
  return NFA::Machine(nfa.START_STATE, nfa.GetTokenState(token));
}

} // naemspace lexer