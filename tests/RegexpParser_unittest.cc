//
// Created by neverchanje on 1/10/16.
//

#include <gtest/gtest.h>
#include "RegexpParser.h"

using namespace lexer;

TEST(ParseLiteral, Basic) {
  RegexpParser parser;
  parser.Parse("abc");

//  <from:2, sym:99, to:3>
//  <from:1, sym:98, to:2>
//  <from:0, sym:97, to:1>
  parser.GetNFA().ToDFA().Dump();
  EXPECT_EQ(false, parser.Match("ab"));
  EXPECT_EQ(true, parser.Match("abc"));
}

TEST(ParseUniqueOperator, Basic) {
  RegexpParser parser;
  parser.Parse("a*b+c?");
//  <from:1, sym:98, to:2>
//  <from:1, sym:97, to:1>
//  <from:2, sym:99, to:3>
//  <from:2, sym:98, to:2>
//  <from:0, sym:98, to:2>
//  <from:0, sym:97, to:1>
  parser.GetNFA().ToDFA().Dump();
  EXPECT_EQ(false, parser.Match("aaac"));
  EXPECT_EQ(true, parser.Match("bbbbc"));
  EXPECT_EQ(false, parser.Match("aaaac"));
  EXPECT_EQ(true, parser.Match("aaaab"));
}

TEST(ParseOr, Basic) {
  RegexpParser parser;
  parser.Parse("b|c");
//  <from:0, sym:99, to:2>
//  <from:0, sym:98, to:1>
  parser.GetNFA().ToDFA().Dump();
}

TEST(ParseOrParen, Basic) {
  RegexpParser parser;
  parser.Parse("(a*)|c");
//  <from:1, sym:97, to:1>
//  <from:0, sym:99, to:2>
//  <from:0, sym:97, to:1>
  parser.GetNFA().ToDFA().Dump();
}

TEST(Paser_Complex01, Complex) {
  RegexpParser parser;
  parser.Parse("((a*)|(b+)|(c?))(a|d)");

//  <from:1, sym:100, to:4>
//  <from:1, sym:97, to:1>
//  <from:2, sym:100, to:4>
//  <from:2, sym:98, to:2>
//  <from:2, sym:97, to:5>
//  <from:3, sym:100, to:4>
//  <from:3, sym:97, to:5>
//  <from:0, sym:100, to:4>
//  <from:0, sym:99, to:3>
//  <from:0, sym:98, to:2>
//  <from:0, sym:97, to:1>
  parser.GetNFA().ToDFA().Dump();
  EXPECT_EQ(true, parser.Match("aaad"));
  EXPECT_EQ(false, parser.Match("aabbc"));
  EXPECT_EQ(true, parser.Match("bbba"));
}
