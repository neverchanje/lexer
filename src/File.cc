//
// Created by neverchanje on 12/1/15.
//

#include <cerrno>
#include <cstdlib>
#include <cassert>
#include "File.h"

using namespace lexer;

// -------------- FileBuf --------------

FileBuf::FileBuf(size_t size) :
    buf(size + 1),
    pos(0),
    bufsz(0) {
}

void FileBuf::Init() {
  buf.clear();
  pos = 0;
  bufsz = 0;
}

// TODO: Set pos to 0 in each Grow.
// This design is hard to implement due to std::vector.
inline void FileBuf::Grow() {
  buf.resize(static_cast<size_t > (bufsz * BUFFER_GROW_FACTOR));
}

inline bool FileBuf::IsFull() {
  return bufsz >= buf.capacity();
}

// -------------- File --------------

File::~File() {
  if (file_) {
    fclose(file_);
  }
}

File::File() {
  file_ = NULL;
}

void File::Reset(FILE *file) {
  if (file_) {
    fclose(file_);
  }
  file_ = file;
}

static FILE *fopenWrap(const char *filename, bool read) {
  FILE *pFile = fopen(filename, read ? "r" : "w");
  // no such file
  if (errno == ENOENT) {
    fprintf(stderr,
            "Opening file %s %s %s",
            filename,
            (read ? "in read mode: " : "in write mode: "),
            strerror(errno));
    abort();
  }
  return pFile;
}

// -------------- FileInput --------------

FileInput::FileInput(const char *filename, size_t size) :
    buf_(size) {
  file_ = fopenWrap(filename, true);
}

void FileInput::Reset(const char *filename) {
  if (file_) {
    fclose(file_);
  }
  file_ = fopenWrap(filename, true);
  buf_.Init();
}

char FileInput::Read() {
  auto &data = buf_.buf;
  size_t &bufsz = buf_.bufsz;
  size_t &pos = buf_.pos;

  // Read from file when there's no buffer can be read.
  if (pos >= bufsz) {
    assert(data[pos] == FileBuf::END_OF_BUFFER || data[pos] == EOF);
    if (buf_.IsFull()) {
      buf_.Grow();
    }
    size_t read = fread(data.data(), 1, data.capacity() - pos, file_);
    bufsz += read;
    data[bufsz] = feof(file_) ? char(EOF) : FileBuf::END_OF_BUFFER;
  }
  return data[pos++];
}

// -------------- FileOutput --------------

FileOutput::FileOutput(const char *filename) {
  file_ = fopenWrap(filename, false);
}

void FileOutput::Reset(const char *filename) {
  if (file_) {
    fclose(file_);
  }
  file_ = fopenWrap(filename, false);
}

size_t FileOutput::Write(FileBuf &buf, size_t size) {
  return fwrite(buf.buf.data(), 1, size, file_);
}
