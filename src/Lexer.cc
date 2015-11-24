//
// Created by neverchanje on 11/20/15.
//

#include "Lexer.h"

using namespace lexer;

//----------------------- Lexer -----------------------
Lexer::Lexer() :
    Lexer(std::cin, std::cout) {
}

Lexer::Lexer(std::istream &in, std::ostream &out) :
    in_(in),
    out_(out),
    buf_(in, InputBuffer::DEFAULT_BUFFER_SIZE) {
}

int Lexer::Scan() {

  while(true) { //loops until an end-of-file character is reached.

  }
}

void Lexer::Restart(std::istream &file) {

}

int Lexer::getNextBuffer() {
  return 0;
}

int Lexer::getChar() {
  InputBuffer::Iterator p;

  //
  if ((*p) == InputBuffer::END_OF_BUFFER_CHAR) {
    switch (getNextBuffer()) {

    }
  }
  return 0;
}

//----------------------- InputBuffer -----------------------

InputBuffer::InputBuffer(std::istream &file, size_t size) :
    bs_(file, size) {
}

void InputBuffer::Flush() {
  bs_.initBuf();
}

//----------------------- InputBuffer::BufferState -----------------------

InputBuffer::BufferState::BufferState(std::istream &file, size_t size) :
    input_file(file),
    buf(size + 2),
    pos(buf.begin()),
    lineno(1),
    column(0),
    bufstatus(Status::NEW) {
  buf[0] = END_OF_BUFFER_CHAR;
  buf[1] = END_OF_BUFFER_CHAR;
}

void InputBuffer::BufferState::initBuf() {
  /* We always need two end-of-buffer characters.  The first causes
   * a transition to the end-of-buffer state.  The second causes
   * a jam in that state.
   */
  buf[0] = END_OF_BUFFER_CHAR;
  buf[1] = END_OF_BUFFER_CHAR;
  pos = buf.begin();
  bufstatus = Status::NEW;
}

