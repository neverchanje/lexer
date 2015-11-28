//
// Created by neverchanje on 9/16/15.
//


#include "DataOutput.h"
#include "FixedBuffer.h"

#define BOOST_TEST_MODULE TestStreamTest
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

using namespace sugen;

class TestStream: public DataOutput {

 public:

  static const int OUTPUT_STREAM_BUFFER_SIZE = 4096;
  typedef FixedBuffer<OUTPUT_STREAM_BUFFER_SIZE> Buffer; //TestStream::Buffer

  const Buffer &buffer() {
    return buf_;
  }

  TestStream() = default;

  void appendBuffer(const char *s, size_t len) override {
    buf_.put(s, len);
  }

  void resetBuffer(void) {
    buf_.reset();
  }

 private:

  Buffer buf_;

};

BOOST_AUTO_TEST_CASE(testDataOutputBooleans) {

  TestStream ts;
  const TestStream::Buffer &buf = ts.buffer();

  BOOST_CHECK_EQUAL(buf.data(), "");
  ts << true;
  BOOST_CHECK_EQUAL(buf.data(), "true");
  ts << '\n';
  BOOST_CHECK_EQUAL(buf.data(), "true\n");
  ts << false;
  BOOST_CHECK_EQUAL(buf.data(), "true\nfalse");

}


BOOST_AUTO_TEST_CASE(testDataOutputShortIntegers) {

  TestStream ts;
  const TestStream::Buffer &buf = ts.buffer();

  ts << 255;
  BOOST_CHECK_EQUAL(buf.data(), "255");
  ts << -1;
  BOOST_CHECK_EQUAL(buf.data(), "255-1");
  ts << 0;
  BOOST_CHECK_EQUAL(buf.data(), "255-10");
  ts << 't';
  BOOST_CHECK_EQUAL(buf.data(), "255-10t");

  ts.resetBuffer();
  ts << 255 << "*" << -1;
  BOOST_CHECK_EQUAL(buf.data(), "255*-1"); //possible wrong case: 255*-1t

}

#include <limits.h>
BOOST_AUTO_TEST_CASE(testDataOutputInteger) {

  TestStream ts;
  const TestStream::Buffer &buf = ts.buffer();

  ts << INT_MAX;
  BOOST_CHECK_EQUAL(buf.data(), "2147483647");

  ts.resetBuffer();
  ts << INT_MIN;
  BOOST_CHECK_EQUAL(buf.data(), "-2147483648");

  ts.resetBuffer();
  ts << SHRT_MAX;
  BOOST_CHECK_EQUAL(buf.data(), "32767");

  ts.resetBuffer();
  ts << SHRT_MIN;
  BOOST_CHECK_EQUAL(buf.data(), "-32768");

  ts.resetBuffer();
  ts << LLONG_MAX;
  BOOST_CHECK_EQUAL(buf.data(), "9223372036854775807");

  ts.resetBuffer();
  ts<<LLONG_MIN;
  BOOST_CHECK_EQUAL(buf.data(), "-9223372036854775808");

  ts.resetBuffer();
  ts<<ULLONG_MAX;
  BOOST_CHECK_EQUAL(buf.data(), "18446744073709551615");

  ts.resetBuffer();
  ts<<UINT32_MAX;
  BOOST_CHECK_EQUAL(buf.data(), "4294967295");

  ts.resetBuffer();
  ts<<UINT16_MAX;
  BOOST_CHECK_EQUAL(buf.data(), "65535");
}


