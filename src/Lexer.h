//
// Created by neverchanje on 11/20/15.
//

#ifndef LEXER_LEXER_H
#define LEXER_LEXER_H

#include <boost/noncopyable.hpp>
#include <iostream>

// Interface of a general scanner.
class ILexer: boost::noncopyable {
 public:

  ILexer(std::istream &input, std::ostream &output) = default;

  // Use std::cin and std::cout as default input and output stream.
  ILexer() :
      ILexer(std::cin, std::cout) {
  }

  virtual int Scan() = 0;

  // Immediately switch to another file input stream.
  virtual void Restart(std::istream &file) = 0;

  // The token corresponding to the matched pattern.
  const char *TokenData() { return token_.data(); }
  size_t TokenLen() { return token_.length(); }

 protected:
  std::string token_;
};

class InputBuffer;
class Lexer: public ILexer {
 public:

  Lexer(std::istream &in, std::ostream &out) :
      in_(in),
      out_(out),
      buf_(in, InputBuffer::MAX_BUFFER_SIZE) {
  }

  int Scan() {

  }

  void Restart(std::istream &file) {

  }

 private:

  std::istream &in_;
  std::ostream &out_;
  InputBuffer buf_;

 private:

  int getNextBuffer() {

  }

};

/**
 * Buffer read from input file.
 */
class InputBuffer: boost::noncopyable {
 public:

  static const int MAX_BUFFER_SIZE = (1 << 16);

  InputBuffer(std::istream &file, size_t size) :
      bs_(file, size) {
  }

  void flush() {

  }

  static const char END_OF_BUFFER_CHAR = '\0';

 private:

  struct BufferState {

    enum Status {
      NEW,
      NORMAL,
      /* When an EOF's been seen but there's still some text to process
       * then we mark the buffer as YY_EOF_PENDING, to indicate that we
       * shouldn't try reading from the input source any more.  We might
       * still have a bunch of tokens to match, though, because of
       * possible backing-up.
       *
       * When we actually see the EOF, we change the status to "new"
       * (via yyrestart()), so that the user can continue scanning by
       * just pointing yyin at a new input file.
       */
          EOF_PENDING
    };

    BufferState(std::istream &file, size_t size) :
        input_file(file),
        bufsize(size),
        pos(&buf[0]),
        lineno(0),
        column(0) {
      buf[0] = END_OF_BUFFER_CHAR;
      buf[1] = END_OF_BUFFER_CHAR;
    }

    //Initialize or reinitialize the buffer.
    void init_buf() {
      /* We always need two end-of-buffer characters.  The first causes
       * a transition to the end-of-buffer state.  The second causes
       * a jam in that state.
       */
      buf[0] = END_OF_BUFFER_CHAR;
      buf[1] = END_OF_BUFFER_CHAR;
      pos = &buf[0];
      bufstatus = Status::NEW;
    }

    std::istream &input_file;

    char buf[bufsize + 2]; // +2 for EOB character.
    char *pos;
    const size_t bufsize;
    unsigned int lineno, column;
    Status bufstatus;
  };

  BufferState bs_;
};


#endif //LEXER_LEXER_H
