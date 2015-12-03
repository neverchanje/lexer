//
// Created by neverchanje on 11/28/15.
//

#include "Rule.h"

namespace lexer {

namespace detail {
int global_pattern_id = 0;
}

int NewPatternID() {
  return TokenID::TOKENID_NUM + detail::global_pattern_id++;
}

} // namespace lexer