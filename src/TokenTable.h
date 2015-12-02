//
// Created by neverchanje on 11/25/15.
//

#ifndef LEXER_TOKENTABLE_H
#define LEXER_TOKENTABLE_H

#include <unordered_map>
#include <string>
#include <functional>

namespace lexer {

enum TokenType {
  NAME,
  WHITESPACE,
  NEWLINE,
  TOKEN_TYPE_NUM
};

/**
 * Example:
 * TokenTable["Foo123"] = TokenType::NAME
 */
typedef std::unordered_map<std::string, TokenType> TokenTable;

const char *GetTokenType(TokenType type);

/**
 * Example:
 * ActionTable[TokenType::WHITESPACE] = [](){ do nothing }
 */
typedef std::function<void()> ActionFunc;
typedef std::unordered_map<TokenType, ActionFunc> ActionTable;

} // namespace lexer

#endif //LEXER_TOKENTABLE_H