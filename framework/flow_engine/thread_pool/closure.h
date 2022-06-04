#pragma once

#include <functional>

namespace flow_engine {
namespace thread_pool {

typedef std::functional<void()> Closure;

template <class T, class ...Args>
inline Closure* NewClosure(T format, args...) {
  return new std::function<void()>(std::bind(format, args...));
}

inline void DeleteClosure(Closure** task) {
  if (!task || !*task) {
    return;
  }
  delete *task;
  *task = nullptr;
}

inline void RunClosure(Closure** task) {
  if (!task || !*task) {
    return;
  }
  (**task)();
  delete *task;
  *task = nullptr;
}

} // namespace thread_pool
} // namespace flow_engine
