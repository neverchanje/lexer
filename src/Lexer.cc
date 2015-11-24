//
// Created by neverchanje on 11/20/15.
//

#include "Lexer.h"

using namespace lexer;

Lexer::Lexer() :
    Lexer(std::cin, std::cout) {
}

Lexer::Lexer(std::istream &in, std::ostream &out) :
    in_(in),
    out_(out),
    buf_(in, InputBuffer::MAX_BUFFER_SIZE) {
}

int Lexer::Scan() {
  return 0;
}

void Lexer::Restart(std::istream &file) {

}

int Lexer::getNextBuffer() {
  return 0;
}

InputBuffer::InputBuffer(std::istream &file, size_t size) :
    bs_(file, size) {
}

void InputBuffer::flush() {
}

void InputBuffer::BufferState::init_buf() {
  /* We always need two end-of-buffer characters.  The first causes
   * a transition to the end-of-buffer state.  The second causes
   * a jam in that state.
   */
  buf[0] = END_OF_BUFFER_CHAR;
  buf[1] = END_OF_BUFFER_CHAR;
  pos = 0;
  bufstatus = Status::NEW;
}

InputBuffer::BufferState::BufferState(std::istream &file, size_t size) :
    input_file(file),
    buf(size),
    pos(0),
    lineno(0),
    column(0)
{
  buf[0] = END_OF_BUFFER_CHAR;
  buf[1] = END_OF_BUFFER_CHAR;
}

