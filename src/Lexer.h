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

  ILexer(std::istream &in, std::ostream &out) { }

  ILexer() = default;

  virtual int Scan() = 0;

  // Immediately switch to another file input stream.
  virtual void Restart(std::istream &file) = 0;

  // The token corresponding to the matched pattern.
  const char *TokenData() const { return token_.data(); }
  size_t TokenLen() const { return token_.length(); }

 protected:

  std::string token_;

 protected:

  //Read one character.
  virtual int getChar() = 0;

};

/**
 * Buffer read from input file.
 */
class InputBuffer: boost::noncopyable {
 public:

  InputBuffer(std::istream &file, size_t size);

  // Discard all the buffered characters.
  void Flush();

  size_t Len() const { return bs_.buf.size(); }

  typedef std::vector<char>::iterator Iterator;

  Iterator Pos() const { return bs_.pos; }

 public:

  static const size_t DEFAULT_BUFFER_SIZE = (1 << 16);
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
       * When we actually see the EOF, we change the status to "NEW"
       * (via Restart()), so that the user can continue scanning by
       * just pointing Lexer::in_ at a new input file.
       */
          EOF_PENDING
    };

    // The two-character-EOB is not counted into size.
    // So the actual size of buffer is (size+2).
    BufferState(std::istream &file, size_t size);

    //Initialize or reinitialize the buffer.
    void initBuf();

    std::istream &input_file;
    std::vector<char> buf; //buf always has two EOB characters at the end.
    Iterator pos;
    unsigned int lineno, column;
    Status bufstatus;
  };

  BufferState bs_;
};

class Lexer: public ILexer {
 public:

  // Create an instance of Lexer by specifying the input and output stream.
  Lexer(std::istream &in, std::ostream &out);

  // Use std::cin and std::cout as default input and output stream.
  Lexer();

  int Scan();

  void Restart(std::istream &file);

 public:

  // The actions we shall do when an end-of-buffer character is hit.
  enum EOBAction {
    CONTINUE_SCAN,
    END_OF_FILE,
    LAST_MATCH
  };

 private:

  std::istream &in_;
  std::ostream &out_;
  InputBuffer buf_;

 private:

  int getNextBuffer();

  int getChar();

};

} //namespace lexer

#endif //LEXER_LEXER_H
