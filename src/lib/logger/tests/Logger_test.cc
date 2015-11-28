//
// Created by neverchanje on 9/18/15.
//

#define BOOST_TEST_MODULE LoggerTest
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "Logger.h"

BOOST_AUTO_TEST_CASE(testLogTrace) {
  LOG_TRACE << true;
  LOG_TRACE << "asdf21402-3";
}

BOOST_AUTO_TEST_CASE(testLogFatal) {
  //There's ought to be have exactly one failure test.
  LOG_FATAL << "joiwe 12";
  //unknown location:0: fatal error in "testLogFatal": signal: SIGABRT (application abort requested)
  //This log statement must not be executed.
  LOG_FATAL << "5602.546";
}

BOOST_AUTO_TEST_CASE(testLogInfo) {
  LOG_INFO << "hello" << 1.293083 << " " << 0.11;
}