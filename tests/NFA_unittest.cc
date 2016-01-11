//
// Created by neverchanje on 12/3/15.
//

#include <gtest/gtest.h>
#include "DFA.h"
#include "NFA.h"
#include "DFATestHelper.h"

using namespace lexer;

TEST(NFA_EpsClosure, NFA_EpsClosure_Test) {

  NFA nfa;
  NFA::State s[5];

  for (int i = 0; i < 5; i++)
    s[i] = nfa.MakeState();

  nfa.AddTrans(s[0], NFA::SYM_EPSILON, s[1]);
  nfa.AddTrans(s[0], NFA::SYM_EPSILON, s[2]);
  nfa.AddTrans(s[1], NFA::SYM_EPSILON, s[3]);
  nfa.AddTrans(s[1], 'a', s[4]);
  nfa.AddTrans(s[2], 'a', s[4]);

//  <from:3, sym:97, to:5>
//  <from:2, sym:97, to:5>
//  <from:2, sym:257, to:4>
//  <from:1, sym:257, to:3>
//  <from:1, sym:257, to:2>
//  nfa.Dump();

  NFA::EpsClosure eps;
  nfa.GetEpsClosure(std::vector<NFA::State>({1}), eps);
  NFA::EpsClosure ts({1, 2, 3, 4});

  EXPECT_EQ(ts, NFA::StateSet({1, 2, 3, 4}));
  EXPECT_EQ(ts, eps);
}

class TestNFA1: public ::testing::Test {
 protected:

  virtual void SetUp() {
    NFA::State s1 = nfa.MakeState(),
        s2 = nfa.MakeState(),
        s3 = nfa.MakeState();

    nfa.AddTrans(NFA::START_STATE, 'a', s1);
    nfa.AddTrans(NFA::START_STATE, 'b', s2);
    nfa.AddTrans(s1, NFA::SYM_EPSILON, s3);
    nfa.AddTrans(s2, NFA::SYM_EPSILON, s3);

//  <from:2, sym:257, to:3>
//  <from:1, sym:257, to:3>
//  <from:0, sym:98, to:2>
//  <from:0, sym:97, to:1>
//  nfa.Dump();
  }

  NFA nfa;
};

TEST_F(TestNFA1, NFA_GetEpsClosure) {
  NFA::StateSet ts;
  nfa.GetEpsClosure({0}, ts);
  EXPECT_EQ(ts, NFA::StateSet({0}));

  nfa.GetEpsClosure({1}, ts);
  EXPECT_EQ(ts, NFA::StateSet({1, 3}));

  nfa.GetEpsClosure({2}, ts);
  EXPECT_EQ(ts, NFA::StateSet({2, 3}));
}

TEST_F(TestNFA1, NFA_ToDFA_01) {
  DFA actual = nfa.ToDFA();

//  <from:0, sym:98, to:1>
//  <from:0, sym:97, to:2>
  DFA expect;
  expect.AddTrans(0, 'a', 1);
  expect.AddTrans(0, 'b', 2);
  EXPECT_PRED_FORMAT2 (AssertDFACmp, expect, actual);
}

TEST(NFA_ToDFA_02, NFA_ToDFA_Test) {
// dragon book figure 3.34

  NFA nfa;

  NFA::State s[11];
  for (int i = 1; i <= 9; ++i) {
    s[i] = nfa.MakeState();
  }

  nfa.AddTrans(NFA::START_STATE, NFA::SYM_EPSILON, s[1]);
  nfa.AddTrans(NFA::START_STATE, NFA::SYM_EPSILON, s[7]);
  nfa.AddTrans(s[1], NFA::SYM_EPSILON, s[2]);
  nfa.AddTrans(s[1], NFA::SYM_EPSILON, s[4]);
  nfa.AddTrans(s[2], 'a', s[3]);
  nfa.AddTrans(s[4], 'b', s[5]);
  nfa.AddTrans(s[3], NFA::SYM_EPSILON, s[6]);
  nfa.AddTrans(s[5], NFA::SYM_EPSILON, s[6]);
  nfa.AddTrans(s[6], NFA::SYM_EPSILON, s[1]);
  nfa.AddTrans(s[6], NFA::SYM_EPSILON, s[7]);
  nfa.AddTrans(s[7], 'a', s[8]);
  nfa.AddTrans(s[8], 'b', s[9]);

  NFA::EpsClosure E;
  nfa.GetEpsClosure(std::vector<NFA::State>({NFA::START_STATE}), E);
  EXPECT_EQ(NFA::StateSet({0, 1, 2, 4, 7}), E);

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

//  DFA dfa = nfa.ToDFA();
//  dfa.Dump();
}

TEST(NFA_ToDFA_03, NFA_ToDFA_Test) {
  NFA nfa;

  NFA::State s[7];
  for (int i = 1; i <= 6; ++i) {
    s[i] = nfa.MakeState();
  }

  nfa.AddTrans(0, NFA::SYM_EPSILON, 5);
  nfa.AddTrans(5, NFA::SYM_EPSILON, 3);
  nfa.AddTrans(5, 'b', 6);
  nfa.AddTrans(4, NFA::SYM_EPSILON, 6);
  nfa.AddTrans(3, NFA::SYM_EPSILON, 1);
  nfa.AddTrans(3, NFA::SYM_EPSILON, 4);
  nfa.AddTrans(4, NFA::SYM_EPSILON, 3);
  nfa.AddTrans(2, NFA::SYM_EPSILON, 4);
  nfa.AddTrans(1, 'a', 2);

  NFA::EpsClosure ts;
  nfa.GetEpsClosure({0}, ts);
  EXPECT_EQ(NFA::EpsClosure({0, 5, 3, 1, 4, 6}), ts);

  nfa.GetEpsClosure({6}, ts);
  EXPECT_EQ(NFA::EpsClosure({6}), ts);

  nfa.GetEpsClosure({2}, ts);
  EXPECT_EQ(NFA::EpsClosure({1, 2, 4, 3, 6}), ts);

  nfa.ToDFA().Dump();
}