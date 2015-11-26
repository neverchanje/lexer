//
// Created by neverchanje on 11/25/15.
//

#include "NFA.h"

using namespace lexer;

EpsClosure NFA::GetEpsClosure(const std::vector<State> &T) {
  std::vector<State> S = T;
  while (!S.empty()) {
    State v = S.back();
    S.pop_back();
  }
}

void NFA::AddTrans(State from, int sym, State to) {

}

void NFA::Dump(State start) {

}