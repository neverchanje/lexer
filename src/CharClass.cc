//
// Created by neverchanje on 11/26/15.
//

#include "CharClass.h"

using namespace lexer;

void CharClass::Add(char c) {
  charset_.set(static_cast<size_t>(c));
}

bool CharClass::Contains(char c) const {
//  return negated_ == !charset_.test(static_cast<size_t>(c));
  if (negated_)
    return !charset_.test(static_cast<size_t>(c));
  else
    return charset_.test(static_cast<size_t>(c));
}

void CharClass::Negate() {
  negated_ = true;
}

void CharClass::Dump() const {
  fprintf(stderr, "[");

  bool has = false;
  for (size_t i = 0; i < CHAR_SIZE; i++) {
    if (charset_.test(i)) {
      if (has)
        fprintf(stderr, ", ");
      else
        has = true;
      fprintf(stderr, "%lu", i);
    }
  }
  fprintf(stderr, "]\n");
}

CharClass::CharClass(const std::string &set) {
  for (int i = 0; i < set.length(); i++) {
    Add(set[i]);
  }
}
