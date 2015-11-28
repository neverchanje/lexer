//
// Created by neverchanje on 9/9/15.
//

#include "TimeValue.h"

#include <sys/time.h>
#include <inttypes.h> //PRId64

namespace sugen {

static_assert(sizeof(TimeValue) == 16, "sizeof(TimeValue) is not equal to 16");

TimeValue TimeValue::diff(const TimeValue &other) {
  int64_t diff = other.getMicrosSinceEpoch() - microsSinceEpoch_;
  diff = diff < 0 ? -diff : diff;
  return TimeValue(diff);
}

std::string TimeValue::toString() {
  char buf[32] = {0};
  snprintf(buf, sizeof(buf), "%" PRId64 ".%06" PRId64 "",
           getSeconds(), getMicros());
  return std::string(buf);
}

std::string TimeValue::toFormattedString() {
  char buf[32] = {0};
  struct tm tm_time;
  time_t seconds = static_cast<time_t>(getSeconds());
  gmtime_r(&seconds, &tm_time); //thread_safe
  snprintf(buf, sizeof(buf), "%4d%02d%02d %02d:%02d:%02d",
           tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
           tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec);
  return std::string(buf);
}

std::string TimeValue::toLocalFormattedString() {
  char buf[32] = {0};
  struct tm tm_time;
  time_t seconds = static_cast<time_t>(getSeconds());
  localtime_r(&seconds, &tm_time); //thread_safe
  snprintf(buf, sizeof(buf), "%4d%02d%02d %02d:%02d:%02d",
           tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
           tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec);
  return std::string(buf);
}

TimeValue TimeValue::now(void) {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return TimeValue(tv.tv_sec, tv.tv_usec);
}

TimeValue &TimeValue::add(double seconds) {
  microsSinceEpoch_ += seconds * kMicrosPerSecond;
  return *this;
}

TimeValue &TimeValue::add(const TimeValue &v) {
  microsSinceEpoch_ += v.microsSinceEpoch_;
  return *this;
}

} // namespace sugen