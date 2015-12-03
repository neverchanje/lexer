//
// Created by neverchanje on 12/3/15.
//

#include <gtest/gtest.h>
#include "NFA.h"
#include <iostream>

using namespace lexer;

TEST(NFA_EpsClosure, NFA_EpsClosure_Test) {

  NFA nfa;
  State s[5];

  for (int i = 0; i < 5; i++)
    s[i] = nfa.MakeState();

  nfa.AddTrans(s[0], SYM_EPSILON, s[1]);
  nfa.AddTrans(s[0], SYM_EPSILON, s[2]);
  nfa.AddTrans(s[1], SYM_EPSILON, s[3]);
  nfa.AddTrans(s[1], 'a', s[4]);
  nfa.AddTrans(s[2], 'a', s[4]);

//  <from:3, sym:97, to:5>
//  <from:2, sym:97, to:5>
//  <from:2, sym:257, to:4>
//  <from:1, sym:257, to:3>
//  <from:1, sym:257, to:2>
//  nfa.Dump();

  EpsClosure eps = nfa.GetEpsClosure({1});
  EpsClosure ts({1, 2, 3, 4});

  EXPECT_EQ(ts, std::set<State>({1, 2, 3, 4}));
  EXPECT_EQ(ts, eps);
}
