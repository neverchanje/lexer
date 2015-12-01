//
// Created by neverchanje on 11/22/15.
//

#include "Lexer.h"
#include "Scanner.h"

using namespace lexer;

int main(int argc, char **argv) {
  Lexer l;
  l.SetInputFile("test.in");
  l.SetOutputFile("test.out");
  while(l.Scan()) {

  }
}