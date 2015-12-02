//
// Created by neverchanje on 15/9/14.
//

#include <stdlib.h> //abort
#include <thread>

#include "Logger.h"
#include "ThisThread.h"
#include "TimeValue.h"

namespace sugen {

namespace detail {

void defaultFlush() {
  ::fflush(stdout);
}

void defaultWrite(const char *msg, size_t len) {
  ::fwrite(msg, 1, len, stdout);
}

Logger::FlushFunc g_FlushFunc = defaultFlush;
Logger::WriteFunc g_WriteFunc = defaultWrite;

/**
 * Fix length of 6.
 */
const char LogLevelNames[Logger::LogLevel::NUM_LOG_LEVELS][7] = {
    "TRACE ",
    "DEBUG ",
    "INFO  ",
    "WARN  ",
    "ERROR ",
    "FATAL "
};

} // namespace detail

struct Logger::LoggerImpl { //: boost::noncopyable
  LoggerImpl(const char *file, int line, LogLevel level);

  const char *getBaseName(const char *fileName) const;

  LogStream stream_;
  LogLevel level_;
  const char *basename_;
  int line_;
  TimeValue time_;
};

Logger::LoggerImpl::LoggerImpl(const char *file, int line, Logger::LogLevel level) :
    basename_(getBaseName(file)),
    level_(level),
    line_(line),
    time_(TimeValue::now()) {
  stream_ << time_.toFormattedString() << " ";
//  stream_ << ThisThread::getId() << " ";
  stream_ << detail::LogLevelNames[level];
}

const char *Logger::LoggerImpl::getBaseName(const char *fileName) const {
  const char *base = strrchr(fileName, '/');
  return base ? base + 1 : fileName;
}

Logger::Logger(const char *file, int line, Logger::LogLevel level) :
    impl_(new LoggerImpl(file, line, level)) {
}

Logger::Logger(const char *file, int line, Logger::LogLevel level, const char *func) :
    impl_(new LoggerImpl(file, line, level)) {
  impl_->stream_ << func << " ";
}

Logger::LogStream &Logger::stream() {
  return impl_->stream_;
}

void Logger::flush() {
  detail::g_FlushFunc();
}

void Logger::setWriteFunc(WriteFunc func) {
  detail::g_WriteFunc = func;
}

void Logger::setFlushFunc(FlushFunc func) {
  detail::g_FlushFunc = func;
}

Logger::~Logger() {
  const LogStream::Buffer &buf = stream().buffer();
  stream() << " " << impl_->basename_ << " line" << impl_->line_ << '\n';
  detail::g_WriteFunc(buf.data(), buf.size());
  flush();
  if (impl_->level_ == LogLevel::FATAL) {
    abort();
  }
}

} //namespace sugen