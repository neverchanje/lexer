//
// Created by neverchanje on 11/25/15.
//

#ifndef LEXER_TOKENTABLE_H
#define LEXER_TOKENTABLE_H

#include <unordered_map>
#include <string>
#include "NFA.h"

namespace lexer {

class Machine;

// reserved
enum TokenID {
  NAME,
  WS,
  OPTWS,
  NEWLINE,
  DEF_VALID_LETTER, // a-zA-Z0-9|+?*()[]
  LOWER_CASE_LETTER, // a-z
  UPPER_CASE_LETTER, // A-Z
  DIGIT, // 0-9
  TOKEN_NUM
};

const char *GetToken(TokenID type);

/**
 * Example:
 * TokenTable["Foo123"] = TokenID::NAME
 */
typedef std::unordered_map<std::string, TokenID> TokenTable;

Machine ToMachine(NFA &nfa, TokenID token);

} // namespace lexer

#endif //LEXER_TOKENTABLE_H