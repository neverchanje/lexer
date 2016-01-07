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
  DEF_OR, // |
  DEF_PLUS, // +
  DEF_OPT, // ?
  DEF_STAR, // *
  LEFT_BRACKET, // (
  RIGHT_BRACKET, // )
  DEF_CC_START, // [
  DEF_CC_END,  // ]
  DEF_CC_CONNECTOR, // -
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

} // namespace lexer

#endif //LEXER_TOKENTABLE_H