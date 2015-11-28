//
// Created by neverchanje on 9/3/15.
//

#include <assert.h>
//BOOST_STATIC_ASSERT free you to add message in static_assert.
#include <boost/static_assert.hpp>
#include <algorithm>

#include "Fmt.h"
#include "DataOutput.h"

namespace sugen {

/**
 * convertToHex is almost ten times better than snprintf("%p", p);
 */
static char digit_hex[] = "0123456789abcdef";
void DataOutput::formatPtrToString(const void *p) {
  uintptr_t v = reinterpret_cast<uintptr_t>(p);
  char buf[32];
  char *cur = buf;
  size_t len;

  *cur++ = '0';
  *cur++ = 'x';
  while (v) {
    *cur++ = digit_hex[v % 16];
    v /= 16;
  }
  *cur = '\0';
  len = cur - buf;
  std::reverse(buf + 2, buf + len);
  appendBuffer(buf, len);
}

template<typename T>
void DataOutput::formatIntToString(T v) {
  BOOST_STATIC_ASSERT(std::is_integral<T>::value);
  fmt::FormatInt f(v);
  appendBuffer(f.c_str(), f.size());
}

//TODO: replace it with google/Double-Conversion
template<typename T>
void DataOutput::formatFloatToString(T v) {
  BOOST_STATIC_ASSERT(std::is_floating_point<T>::value);
  char buf[32];

  int len = snprintf(buf, sizeof(buf), "%lf", v);
  appendBuffer(buf, static_cast<size_t>(len));
}


DataOutput &DataOutput::operator<<(unsigned int v) {
  formatIntToString(v);
  return *this;
}

DataOutput &DataOutput::operator<<(int v) {
  formatIntToString(v);
  return *this;
}

DataOutput &DataOutput::operator<<(unsigned long v) {
  formatIntToString(v);
  return *this;
}

DataOutput &DataOutput::operator<<(long v) {
  formatIntToString(v);
  return *this;
}

DataOutput &DataOutput::operator<<(long long v) {
  formatIntToString(v);
  return *this;
}

DataOutput &DataOutput::operator<<(unsigned long long v) {
  formatIntToString(v);
  return *this;
}

DataOutput &DataOutput::operator<<(double v) {
  formatFloatToString(v);
  return *this;
}

DataOutput &DataOutput::operator<<(const void *ptr) {
  formatPtrToString(ptr);
  return *this;
}

} //namespace sugen