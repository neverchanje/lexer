//
// Created by neverchanje on 11/24/15.
//

#include <string>
#include <sstream>
#include "DFA.h"

namespace lexer {

typedef DFA::State State;

void DFA::AddTrans(State from, SymbolID sym, State to) {
  trans_[from][sym] = to;
}

bool DFA::HasTrans(State from, SymbolID sym) const {
  if (trans_.find(from) == trans_.end()) {
    return false;
  }
  auto &t1 = trans_.find(from)->second;
  return (t1.find(sym) != t1.end());
}

boost::optional<State> DFA::GetTrans(State from, SymbolID sym) const {
  auto found1 = trans_.find(from);
  if (found1 == trans_.end())
    return boost::none;

  auto found2 = found1->second.find(sym);
  if (found2 == found1->second.end())
    return boost::none;
  return found2->second;
}

void DFA::Dump() const {
  fprintf(stderr, "\n------- Begining of dumping the DFA. -------\n");
  fprintf(stderr, "%s\n", ToString().c_str());
  fprintf(stderr, "------- Ending of dumping the DFA. -------\n");
}

std::string DFA::ToString() const {
  std::string ret;
  std::stringstream ss;
  ret += "\n";
  for (auto t1 = trans_.begin(); t1 != trans_.end(); t1++) {
    for (auto t2 = t1->second.begin(); t2 != t1->second.end(); t2++) {
      ss << "<from:" << t1->first
          << ", sym:" << t2->first
          << ", to:" << t2->second
          << ">\n";
      ret += ss.str();
      ss.str(""); // clear the content of the stringstream
    }
  }
  return ret;
}

} // namespace lexer