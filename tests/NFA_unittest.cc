//
// Created by neverchanje on 12/3/15.
//

#include <gtest/gtest.h>
#include "DFA.h"
#include "NFA.h"

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
  nfa.Dump();

  EpsClosure eps;
  nfa.GetEpsClosure({1}, eps);
  EpsClosure ts({1, 2, 3, 4});

  EXPECT_EQ(ts, std::set<State>({1, 2, 3, 4}));
  EXPECT_EQ(ts, eps);
}

TEST(NFA_ToDFA_01, NFA_ToDFA_Test) {

  NFA nfa;

  State s1 = nfa.MakeState(),
      s2 = nfa.MakeState(),
      s3 = nfa.MakeState();

  nfa.AddTrans(nfa.Start(), 'a', s1);
  nfa.AddTrans(nfa.Start(), 'b', s2);
  nfa.AddTrans(s1, SYM_EPSILON, s3);
  nfa.AddTrans(s2, SYM_EPSILON, s3);
  nfa.AddTrans(s3, SYM_EPSILON, nfa.Final());

//  <from:3, sym:257, to:-1>
//  <from:2, sym:257, to:3>
//  <from:1, sym:257, to:3>
//  <from:0, sym:98, to:2>
//  <from:0, sym:97, to:1>
  nfa.Dump();

  DFA dfa = nfa.ToDFA();

//  <from:0, sym:97, to:2>
//  <from:0, sym:98, to:1>
  dfa.Dump();
}

TEST(NFA_ToDFA_02, NFA_ToDFA_Test) {
// dragon book figure 3.34

  NFA nfa;

  State s[11];
  for (int i = 1; i <= 9; ++i) {
    s[i] = nfa.MakeState();
  }

  nfa.AddTrans(nfa.Start(), SYM_EPSILON, s[1]);
  nfa.AddTrans(nfa.Start(), SYM_EPSILON, s[7]);
  nfa.AddTrans(s[1], SYM_EPSILON, s[2]);
  nfa.AddTrans(s[1], SYM_EPSILON, s[4]);
  nfa.AddTrans(s[2], 'a', s[3]);
  nfa.AddTrans(s[4], 'b', s[5]);
  nfa.AddTrans(s[3], SYM_EPSILON, s[6]);
  nfa.AddTrans(s[5], SYM_EPSILON, s[6]);
  nfa.AddTrans(s[6], SYM_EPSILON, s[1]);
  nfa.AddTrans(s[6], SYM_EPSILON, s[7]);
  nfa.AddTrans(s[7], 'a', s[8]);
  nfa.AddTrans(s[8], 'b', s[9]);
  nfa.AddTrans(s[9], 'b', nfa.Final());

  EpsClosure E;
  nfa.GetEpsClosure(std::vector<State>({nfa.Start()}), E);
  EXPECT_EQ(std::set<int>({0, 1, 2, 4, 7}), E);

//  <from:9, sym:98, to:-1>
//  <from:8, sym:98, to:9>
//  <from:7, sym:97, to:8>
//  <from:6, sym:257, to:7>
//  <from:6, sym:257, to:1>
//  <from:5, sym:257, to:6>
//  <from:3, sym:257, to:6>
//  <from:4, sym:98, to:5>
//  <from:2, sym:97, to:3>
//  <from:1, sym:257, to:4>
//  <from:1, sym:257, to:2>
//  <from:0, sym:257, to:7>
//  <from:0, sym:257, to:1>
  nfa.Dump();

  DFA dfa = nfa.ToDFA();

  dfa.Dump();
}
