//
// Created by neverchanje on 1/10/16.
//

#include <gtest/gtest.h>
#include "RegexpParser.h"

using namespace lexer;

TEST(ParseLiteral, Basic) {
  RegexpParser parser;
  parser.Parse("abc");
  parser.GetNFA().Dump();
}