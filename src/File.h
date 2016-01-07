//
// Created by neverchanje on 11/28/15.
//

#ifndef LEXER_FILE_H
#define LEXER_FILE_H

#include <cstdio>
#include <vector>

#include "DisallowCopying.h"

//TODO: handling exception.

namespace lexer {

/**
 * A FileBuf object reads from a given input file.
 */
struct FileBuf {
  __DISALLOW_COPYING__(FileBuf);

  static const size_t DEFAULT_BUFFER_SIZE = (1 << 16);
  
  // End of buffer is differnt from EOF, it denotes that there's no data
  // can be read from the FileBuf.
  static const char END_OF_BUFFER = '\0';

  // The foolish compiler warns me if I use const rather than constexpr.
  static constexpr float BUFFER_GROW_FACTOR = 1.5f;

  /* static const size_t MAX_BUFFER_SIZE = std::numeric_limit<int>::max(); */

  // The internal buffer array where the data is stored.
  std::vector<char> buf;

  // There's no data is readable from FileBuf when pos is hit the EOB character,
  // or the value of pos is no less than bufsz.
  //
  // pos is always in the range of [0, bufsz]
  size_t pos;

  // std::vector always sets size() to capacity() when we specify its initial
  // size. It's weird and therefore we maintain the real size `bufsz`.
  // `bufsz` is one greater than the index of the last valid byte in the buffer.
  size_t bufsz;

  // The initial size of FileBuf should be at least 1 to store the EOB character.
  FileBuf(size_t size);
  FileBuf() : FileBuf(DEFAULT_BUFFER_SIZE) { }

  void Init();

  void Grow();

  bool IsFull();
};

/**
 * File class encapsulates the FILE pointer in RAII.
 */
class File {
  __DISALLOW_COPYING__(File);

 public:

  File();
  ~File();

  virtual void Reset(const char *filename) = 0;
  void Reset(FILE *file);

  const FILE *GetFilePtr() { return file_; }

 protected:
  FILE *file_;
};

// FileInput is a buffered file reader.
class FileInput: public File {

 public:

  FileInput() = default;

  // Read the content in filename and initialize the buffer size.
  FileInput(const char *filename, size_t size);

  FileInput(const char *filename) :
      FileInput(filename, FileBuf::DEFAULT_BUFFER_SIZE) {
  }

  void Reset(const char *filename);

  // Read one character from the file.
  // If there's content in FileBuf that is unread, then read from
  // FileBuf, if not, read from file to fill the buffer.
  // Return EOF when no more data can be read from the given file.
  char Read();

  FileBuf &GetBufferLVal() { return buf_; }
  const FileBuf &GetBuffer() const { return buf_; }

 private:
  FileBuf buf_;
};

class FileOutput: public File {

 public:

  FileOutput() = default;

  FileOutput(const char *filename);

  void Reset(const char *filename);

  // Return the total number of bytes write from the buffer.
  size_t Write(FileBuf &buf, size_t size);
};

} // namespace lexer

#endif //LEXER_FILE_H