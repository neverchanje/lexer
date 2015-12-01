//
// Created by neverchanje on 12/1/15.
//

#include "File.h"

using namespace lexer;

Buffer::Buffer(size_t size) :
    buf(size),
    pos(0),
    lineno(0),
    column(0) {
  buf[0] = END_OF_BUFFER_CHAR;
}

void Buffer::Init() {
  buf.clear();
  pos = 0;
  lineno = column = 0;
  buf[0] = END_OF_BUFFER_CHAR;
}

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

FileInput::FileInput(const char *filename, size_t size) :
    buf_(size) {
  file_ = fopen(filename, "r");
}

void FileInput::Reset(const char *filename) {
  if (file_) {
    fclose(file_);
  }
  file_ = fopen(filename, "r");
  buf_.Init();
}

char FileInput::Read(size_t size) {
  size_t cap = buf_.buf.capacity();
  size_t bufsz = buf_.buf.size();

  if (cap - bufsz > size) {
  }
  return buf_.buf[buf_.pos++];
}

FileOutput::FileOutput(const char *filename) {
  fopen(filename, "w");
}

void FileOutput::Reset(const char *filename) {
  if (file_) {
    fclose(file_);
  }
  file_ = fopen(filename, "w");
}


size_t FileOutput::Write(Buffer &buf, size_t size) {
  return fwrite(buf.buf.data(), 1, size, file_);
}
