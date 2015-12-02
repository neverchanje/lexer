//
// Created by neverchanje on 12/1/15.
//

#include <cerrno>
#include "File.h"
#include <logger/Logger.h>

using namespace lexer;

// -------------- Buffer --------------

Buffer::Buffer(size_t size) :
    buf(size),
    pos(0),
    lineno(0),
    column(0),
    bufsz(0) {
  buf[0] = END_OF_BUFFER_CHAR;
}

void Buffer::Init() {
  buf.clear();
  pos = 0;
  lineno = column = 0;
  bufsz = 0;
  buf[0] = END_OF_BUFFER_CHAR;
}

// -------------- File --------------

File::~File() {
  if (!file_) {
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
  if (errno == ENOENT) {
    LOG_FATAL
        << "\"Openning file "
        << filename
        << (read ? " in read mode: " : "in write mode: ")
        << strerror(errno) << "\"";
  } else {
    LOG_INFO << "\"Open file "
        << filename
        << (read ? " in read mode" : "in write mode")
        << "\"";
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
  size_t cap = data.capacity();
  size_t bufsz = buf_.bufsz;
  size_t pos = buf_.pos;

  // if there's no buffer can be read
  if (pos >= bufsz) {
    if (cap <= bufsz) { // if the buffer has no room left
      data.resize(static_cast<size_t >(cap * Buffer::BUFFER_GROW_FACTOR));
    }
    size_t read = fread(data.data(), 1, data.capacity() - pos, file_);
    buf_.bufsz += read;
    if (feof(file_)) {
      buf_.bufsz++;
      return data[buf_.pos++];
    }
  }
  return data[buf_.pos++];
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

size_t FileOutput::Write(Buffer &buf, size_t size) {
  return fwrite(buf.buf.data(), 1, size, file_);
}
