//
// Created by neverchanje on 9/3/15.
//

#ifndef SUGEN_LOGSTREAM_H
#define SUGEN_LOGSTREAM_H

#include <boost/noncopyable.hpp>
#include <string>

namespace sugen {

/**
 * DataOutput is an interface for formatting basic types of value
 * into string. It's designed to be an alternative of the formatting
 * function in std::ostream.
 *
 * NOTE: DataOutput doesn't own a stream itself, so the subclasses of
 * DataOutput are required to implement the function `appendBuffer`.
 *
 * @see Logger::LogStream
 */
class DataOutput: boost::noncopyable {

 public:

  virtual ~DataOutput() { }

  /**
   * Raw string will be implicitly promoted to boolean rather than
   * std::string, if we don't override operator<< with 'const char *'.
   */
  DataOutput &operator<<(const char *s) {
    if (s == NULL) {
      appendBuffer("(null)", 6);
    } else {
      appendBuffer(s, strlen(s));
    }
    return *this;
  }

  DataOutput &operator<<(const unsigned char *s) {
    //error: static_cast from 'const unsigned char *' to 'const char *' is not allowed
    return operator<<(reinterpret_cast<const char *>(s));
  }

  DataOutput &operator<<(const std::string &s) {
    return operator<<(s.c_str());
  }

  DataOutput &operator<<(char v) {
    char s[2];
    s[0] = v;
    s[1] = '\0';
    return operator<<(s);
  }

  DataOutput &operator<<(unsigned short v) {
    return operator<<(static_cast<unsigned int>(v));
  }

  DataOutput &operator<<(short v) {
    return operator<<(static_cast<int>(v));
  }

  DataOutput &operator<<(unsigned int v);
  DataOutput &operator<<(int v);
  DataOutput &operator<<(unsigned long v);
  DataOutput &operator<<(long v);
  DataOutput &operator<<(long long v);
  DataOutput &operator<<(unsigned long long v);

  DataOutput &operator<<(bool v) {
    return operator<<(std::string(v ? "true" : "false"));
  }

  DataOutput &operator<<(double v);

  DataOutput &operator<<(float v) {
    return operator<<(static_cast<double>(v));
  }

  /**
   * Print the address pointed by ptr in hexadecimal.
   */
  DataOutput &operator<<(const void *ptr);

 private:

  template<typename T>
  void formatIntToString(T v);

  template<typename T>
  void formatFloatToString(T v);

  void formatPtrToString(const void *ptr);

 protected:

  /**
   * DataOutput reserve the implementation of how you append
   * string to the buffer.
   * `appendBuffer` is used and only used in operator<<.
   */
  virtual void appendBuffer(const char *s, size_t len) = 0;
};

} //namespace sugen


#endif //SUGEN_LOGSTREAM_H
