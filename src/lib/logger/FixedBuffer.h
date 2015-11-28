//
// Created by neverchanje on 9/3/15.
//

#ifndef SUGEN_BUFFER_H
#define SUGEN_BUFFER_H

#include <string>

namespace sugen {

/**
 * FixedBuffer has fixed size, which is given in declaration, and
 * will not be allowed to change the buffer size after creation.
 * FixedBuffer is terminated by '\0'.
 */
template<size_t BUFSIZE>
class FixedBuffer {

 public:

  FixedBuffer() :
      cur_(buf_) {
    memset(buf_, 0, sizeof(buf_));
  }

  ~FixedBuffer() = default;

  //toString
  const char *data(void) const {
    return buf_;
  }

  size_t capacity(void) const {
    return BUFSIZE;
  }

  size_t avail(void) const {
    return BUFSIZE - size();
  }

  size_t size(void) const {
    return cur_ - buf_;
  }

  //Concatenate the contents of s to the buffer.
  //
  void put(const char *s, size_t len) {
    if(len < avail()) {
      memcpy(cur_, s, len);
      cur_ += len;
      *cur_ = '\0';
    }
  }

  void put(const std::string &s) {
    put(s.c_str(), s.length());
  }

  void put(const char *s) {
    put(s, strlen(s));
  }

  void reset(void) {
    cur_ = buf_;
    *cur_ = '\0';
  }

  const char *current(void) const {
    return cur_;
  }

 private:

  char buf_[BUFSIZE];

  char *cur_; //iterator

};

} //namespace sugen

#endif //SUGEN_BUFFER_H
