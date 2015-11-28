//
// Created by neverchanje on 9/8/15.
//

#ifndef SUGEN_TIMEVALUE_H
#define SUGEN_TIMEVALUE_H

#include <string>

namespace sugen {

/**
 * The header <boost/operators.hpp> is too heavy, when it's merely
 * used for boost::less_than_comparable.
 */
template<typename T, typename U = T>
struct less_than_comparable {
  virtual bool operator<(const U &) const = 0;
  friend bool operator>(const T &x, const U &y) { return y < x; }
  friend bool operator>=(const T &x, const U &y) { return !(x < y); }
  friend bool operator<=(const T &x, const U &y) { return !(x > y); }
};

//使用 int64_t 而非 time_t 和 subseconnd_t 作为时间单位的原因是
//使接口更易使用（不必频繁地cast），也不必在头文件中 include <sys/time.h>
/**
 * Time stamp in UTC, in microseconds resolution.
 */
class TimeValue: public less_than_comparable<TimeValue> { //TimeValue is sortable.
//implicit copyable

 public:

  //empty value
  TimeValue() :
      microsSinceEpoch_(0) {
  }

  TimeValue(int64_t sec, int64_t msec) {
    microsSinceEpoch_ = sec * kMicrosPerSecond + msec;
  }

  TimeValue(int64_t ms) :
      microsSinceEpoch_(ms) {
  }

  int64_t getSeconds(void) const {
    return microsSinceEpoch_ / kMicrosPerSecond;
  }

  int64_t getMicros(void) const {
    return microsSinceEpoch_ - microsSinceEpoch_ * kMicrosPerSecond;
  }

  int64_t getMicrosSinceEpoch(void) const {
    return microsSinceEpoch_;
  }

  bool operator<(const TimeValue &other) const override {
    return microsSinceEpoch_ < other.getMicrosSinceEpoch();
  }

  inline std::string toString();

  /**
   * Return the current UTC time in the format of "20151019 07:00:01"
   */
  std::string toFormattedString();

  /**
   * Return the current local time in the format of "20151019 07:00:01"
   */
  std::string toLocalFormattedString();

  static TimeValue now(void); // UTC time

  /**
   * Calculate the difference between two time values.
   */
  TimeValue diff(const TimeValue &other);

  //1e6 is compiled as double.
  static const int kMicrosPerSecond = 1000 * 1000;

  TimeValue &add(double seconds);

  TimeValue &add(const TimeValue &v);

 private:

  int64_t microsSinceEpoch_; //microseconds counted from 1970.1.1 00:00:00

};

} //namespace sugen

#endif //SUGEN_TIMEVALUE_H
