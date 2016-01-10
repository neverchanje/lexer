//
// Created by neverchanje on 1/10/16.
//

#ifndef LEXER_DFATESTHELPER_H
#define LEXER_DFATESTHELPER_H

#include <gtest/gtest.h>
#include "DFA.h"

namespace lexer {

// For the use of gtest.
inline bool DFACmp(const DFA &lhs, const DFA &rhs) {
  return lhs.GetTransTable() == rhs.GetTransTable();
}

::testing::AssertionResult AssertDFACmp(const char *expect_expr,
                                        const char *actual_expr,
                                        const DFA &expect,
                                        const DFA &actual) {
  if (DFACmp(expect, actual))
    return ::testing::AssertionSuccess();

  auto res = ::testing::AssertionFailure();
  res << "Value of: " << actual_expr << std::endl;
  res << "Actual: " << actual.ToString() << std::endl;
  res << "Expected: " << expect_expr << std::endl;
  res << "Which is: " << expect.ToString() << std::endl;
  return res;
}

} // namespace lexer

#endif //LEXER_DFATESTHELPER_H
