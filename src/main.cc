//
// Created by neverchanje on 11/22/15.
//

#include "Lexer.h"

using namespace lexer;

int main(int argc, char **argv) {
  Lexer l;
  l.SetInputFile("/Users/neverchanje/Documents/lexer/src/test.in");
  l.SetOutputFile("/Users/neverchanje/Documents/lexer/src/test.out");
  l.Scan();
}