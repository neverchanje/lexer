//
// Created by neverchanje on 11/28/15.
//

#ifndef LEXER_FILE_H
#define LEXER_FILE_H

#include <boost/noncopyable.hpp>
#include <cstdio>
#include <vector>

//TODO: handling exception.

namespace lexer {

/**
 * Buffer read from input file and will be write to the output file.
 */
struct Buffer {

  static const size_t DEFAULT_BUFFER_SIZE = (1 << 16);

  static const char END_OF_BUFFER_CHAR = '\0';

  typedef std::vector<char>::iterator Iterator;

  std::vector<char> buf;

  Iterator pos;

  unsigned int lineno, column;

  Buffer(size_t size) :
      buf(size),
      pos(buf.begin()),
      lineno(0),
      column(0) {
    buf[0] = END_OF_BUFFER_CHAR;
  }
};

/**
 * File encapsulates the FILE pointer in RAII.
 */
class File: boost::noncopyable {
 public:

  ~File() {
    fclose(file_);
  }

 protected:
  FILE *file_;
};

class FileInput: public File {

 public:

  // default input: stdin
  FileInput() :
      file_(stdin),
      buf_(Buffer::DEFAULT_BUFFER_SIZE) {
  }

  // Read the content in filename and initialize the buffer size.
  FileInput(const char *filename, size_t size) :
      buf_(size) {
    file_ = fopen(filename, "r");
  }

  void Read(size_t size) {
    fread(buf_.buf.data(), size, 1, file_);
  }

  Buffer &GetBuffer() {
    return buf_;
  }

  const Buffer &GetBuffer() const {
    return buf_;
  }

 private:
  Buffer buf_;
};

class FileOutput: public File {

 public:

  // default output: stdout
  FileOutput() :
      file_(stdout) {
  }

  FileOutput(const char *filename) {
    fopen(filename, "w");
  }

  size_t Write(Buffer &buf, size_t size) {
    size_t writen = fwrite(buf.buf.data(), size, 1, file_);
    return writen;
  }
};

} // namespace lexer

#endif //LEXER_FILE_H