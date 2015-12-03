//
// Created by neverchanje on 11/25/15.
//

#ifndef LEXER_TOKENTABLE_H
#define LEXER_TOKENTABLE_H

#include <unordered_map>
#include <string>

namespace lexer {

enum TokenID {
  NAME,
  WS,
  OPTWS,
  NEWLINE,
  TOKENID_NUM
};

const char *GetTokenID(TokenID type);

/**
 * Example:
 * TokenTable["Foo123"] = TokenID::NAME
 */
typedef std::unordered_map<std::string, TokenID> TokenTable;

} // namespace lexer

#endif //LEXER_TOKENTABLE_H