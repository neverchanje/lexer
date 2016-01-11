//
// Created by neverchanje on 1/10/16.
//

#include <gtest/gtest.h>
#include "RegexpParser.h"
#include "DFA.h"

using namespace lexer;

TEST(ParseLiteral, Basic) {
  RegexpParser parser;
  parser.Parse("abc");

//  <from:0, sym:257, to:1>
//  <from:2, sym:257, to:3>
//  <from:4, sym:257, to:5>
//  <from:5, sym:99, to:6>
//  <from:3, sym:98, to:4>
//  <from:1, sym:97, to:2>
  parser.GetNFA().ToDFA().Dump();
}

TEST(ParseUniqueOperator, Basic) {
  RegexpParser parser;
  parser.Parse("a*b+c?");
//  <from:0, sym:257, to:3>
//  <from:10, sym:257, to:12>
//  <from:11, sym:257, to:12>
//  <from:11, sym:257, to:9>
//  <from:9, sym:99, to:10>
//  <from:8, sym:257, to:11>
//  <from:8, sym:257, to:7>
//  <from:6, sym:257, to:8>
//  <from:7, sym:257, to:5>
//  <from:5, sym:98, to:6>
//  <from:4, sym:257, to:7>
//  <from:4, sym:257, to:3>
//  <from:2, sym:257, to:4>
//  <from:3, sym:257, to:4>
//  <from:3, sym:257, to:1>
//  <from:1, sym:97, to:2>
  parser.GetNFA().ToDFA().Dump();
}

TEST(ParseOr, Basic) {
  RegexpParser parser;
  parser.Parse("b|c");
//  <from:0, sym:257, to:3>
//  <from:2, sym:257, to:4>
//  <from:3, sym:257, to:1>
//  <from:3, sym:99, to:4>
//  <from:1, sym:98, to:2>
  parser.GetNFA().ToDFA().Dump();
}

TEST(ParseOrParen, Basic) {
  RegexpParser parser;
  parser.Parse("(a*)|c");
//  <from:0, sym:257, to:5>
//  <from:5, sym:257, to:3>
//  <from:5, sym:99, to:6>
//  <from:4, sym:257, to:6>
//  <from:4, sym:257, to:3>
//  <from:2, sym:257, to:4>
//  <from:3, sym:257, to:4>
//  <from:3, sym:257, to:1>
//  <from:1, sym:97, to:2>
  parser.GetNFA().ToDFA().Dump();
}