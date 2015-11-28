//
// Created by neverchanje on 9/17/15.
//

#ifndef SUGEN_THISTHREAD_H
#define SUGEN_THISTHREAD_H

#include <unistd.h> //syscall
#include <sys/syscall.h> //SYS_gettid

namespace sugen {

/**
 * As we're not allowed to get current thread's id of type 'pid_t', via
 * std::this_thread::get_id, so we need to reinvent this wheel.
 */

namespace ThisThread {

namespace detail {
//cached for later usage.
thread_local pid_t t_tid = 0;
} //namespace detail

pid_t getId(void) {
  if (detail::t_tid) {
    return detail::t_tid;
  }
  detail::t_tid = static_cast<pid_t >(::syscall(SYS_gettid));
  return detail::t_tid;
}

} //namespace ThisThread

} //namespace sugen

#endif //SUGEN_THISTHREAD_H
