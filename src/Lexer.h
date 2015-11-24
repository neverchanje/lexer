//
// Created by neverchanje on 11/20/15.
//

#ifndef LEXER_LEXER_H
#define LEXER_LEXER_H

#include <boost/noncopyable.hpp>
#include <iostream>
#include <vector>


namespace lexer {

// Interface of a general scanner.
class ILexer: boost::noncopyable {
 public:

  ILexer(std::istream &input, std::ostream &output);

  ILexer() = default;

  virtual int Scan() = 0;

  // Immediately switch to another file input stream.
  virtual void Restart(std::istream &file) = 0;

  // The token corresponding to the matched pattern.
  const char *TokenData() { return token_.data(); }
  size_t TokenLen() { return token_.length(); }

 protected:
  std::string token_;
};


/**
 * Buffer read from input file.
 */
class InputBuffer: boost::noncopyable {
 public:

  InputBuffer(std::istream &file, size_t size);

  void flush();

  static const int MAX_BUFFER_SIZE = (1 << 16);

 private:

  static const char END_OF_BUFFER_CHAR = '\0';

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

    BufferState(std::istream &file, size_t size);

    //Initialize or reinitialize the buffer.
    void init_buf();

    std::istream &input_file;
    std::vector<char> buf; //buf always has two EOB characters at the end.
    size_t pos;
    unsigned int lineno, column;
    Status bufstatus;
  };

  BufferState bs_;
};

class Lexer: public ILexer {
 public:

  // Create an instante of Lexer by specifying the input and output stream.
  Lexer(std::istream &in, std::ostream &out);

  // Use std::cin and std::cout as default input and output stream.
  Lexer();

  int Scan();

  void Restart(std::istream &file);

 private:

  std::istream &in_;
  std::ostream &out_;
  InputBuffer buf_;

 private:

  int getNextBuffer();

};

} //namespace lexer

#endif //LEXER_LEXER_H
