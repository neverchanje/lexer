//
// Created by neverchanje on 15/9/14.
//

#ifndef SUGEN_LOGGER_H
#define SUGEN_LOGGER_H

#include <boost/noncopyable.hpp>

#include <memory>

#include "DataOutput.h"
#include "FixedBuffer.h"

namespace sugen {

/**
 * When you finish streaming to an instance of Logger, destructor
 * of Logger is invoked and all buffered message will be streamed
 * to the specified destination.
 *
 * Format of Logger:
 * YYYYMMDD HH:MM::SS THREAD_ID LOG_LEVEL <MESSAGE> FILE_BASENAME LINE
 *
 * Use the LOG_XXX macros to log things.
 *
 * Example:
 * See logger_test.cc.
 *
 * TODO: add LogDestination class.
 * LogDestination is now simply implemented by WriteFunc, FlushFunc.
 */
class Logger: boost::noncopyable {

 public:

  class LogStream: public DataOutput {
   public:

    static const int LOG_STREAM_BUFFER_SIZE = 4096;
    typedef FixedBuffer<LOG_STREAM_BUFFER_SIZE> Buffer; //LogStream::Buffer

    const Buffer &buffer() const { return buf_; }

   private:

    void appendBuffer(const char *s, size_t len) override {
      buf_.put(s, len);
    }

    Buffer buf_;
  };

  struct LoggerImpl;

  enum LogLevel {
    TRACE,
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL,
    NUM_LOG_LEVELS //number of logging levels
  };

  Logger(const char *file, int line, LogLevel level);

  Logger(const char *file, int line, LogLevel level, const char *func);

  ~Logger();

  LogStream &stream();

  /**
   * Flush a buffered message.  Always called by the destructor, it may also
   * be called from elsewhere if needed.
   * // Only the first call is actioned; any later ones are ignored.
   */
  void flush();

  /**
   * WriteFunc and FlushFunc stream the buffered message to stdout by default.
   * We can customize the destination by setWriteFunc and setFlushFunc.
   */
  typedef void (*WriteFunc)(const char *msg, size_t len);
  typedef void (*FlushFunc)();
  void setWriteFunc(WriteFunc func);
  void setFlushFunc(FlushFunc func);

 private:
  std::unique_ptr<LoggerImpl> impl_;
};

} //namespace sugen


#define LOGGER sugen::Logger

/**
 * The logger is always used as a temporary variable, so that it'll be destructed
 * right after the end of the log statement. During the destruction, It writes and
 * flushes the log messages to the disk.
 */

//
#define LOG_TRACE    LOGGER(__FILE__, __LINE__, LOGGER::LogLevel::TRACE, __func__).stream()

#ifndef NDEBUG
  #define LOG_DEBUG    LOGGER(__FILE__, __LINE__, LOGGER::LogLevel::DEBUG, __func__).stream()
#else
  #define LOG_DEBUG LOG_TRACE
#endif

// LOG_INFO gives the progress and chosen state information. This level
// will be generally useful for end user.
#define LOG_INFO     LOGGER(__FILE__, __LINE__, LOGGER::LogLevel::INFO).stream()

#define LOG_WARN     LOGGER(__FILE__, __LINE__, LOGGER::LogLevel::WARN).stream()

#define LOG_ERROR    LOGGER(__FILE__, __LINE__, LOGGER::LogLevel::ERROR).stream()

// Abort if fatal error is occured.
#define LOG_FATAL    LOGGER(__FILE__, __LINE__, LOGGER::LogLevel::FATAL).stream()

// Always-on checking
#define CHECK(x)    if(x){} else LOG_FATAL << "Check failed: " #x
#define CHECK_LT(x, y)    CHECK((x) < (y))
#define CHECK_GT(x, y)    CHECK((x) > (y))
#define CHECK_LE(x, y)    CHECK((x) <= (y))
#define CHECK_GE(x, y)    CHECK((x) >= (y))
#define CHECK_EQ(x, y)    CHECK((x) == (y))
#define CHECK_NE(x, y)    CHECK((x) != (y))

#endif //SUGEN_LOGGER_H
