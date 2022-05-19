#pragma once

#include <pthread.h>

#include <functional>

#include <httpcomm/util/define.h>
#include <httpcomm/util/time_util.h>

HTTPCOMM_NAMESPACE_BEGIN

class Thread {
public:
  typedef std::function<void()> ThreadFunc;

public:
  Thread();

  Thread(const ThreadFunc& threadFunc);

  ~Thread();

  bool Start();

  bool Join();

  bool Detach();

  void SetThreadFunc(ThreadFunc& threadFunc);

  const ThreadFunc& GetThreadFunc() const;

private:
  pthread_t tid_;
  ThreadFunc thread_func_;
  bool started_;

  HTTPCOMM_DISABLE_COPY_ASSIGN(Thread);

};

class Mutex {
public:
  Mutex() { pthread_mutex_init(&mutex_, NULL); }
  
  ~Mutex() { pthread_mutex_destroy(&mutex_); }

  bool Lock() { return pthread_mutex_lock(&mutex_) == 0; }

  bool TryLock() { return pthread_mutex_trylock(&mutex_) == 0; }

  bool Unlock() { return pthread_mutex_unlock(&mutex_) == 0; }

private:
  friend class Cond;

  pthread_mutex_t mutex_;

  HTTPCOMM_DISABLE_COPY_ASSIGN(Mutex);
};

class Cond {
public:
  explicit Cond(Mutex &mutex) : mutex_(mutex) {
    pthread_cond_init(&cond_, NULL);
  }

  ~Cond() { pthread_cond_destroy(&cond_); }

  bool Wait(int64_t us);

  bool Signal() { return pthread_cond_signal(&cond_) == 0; }

  bool BroadCast() { return pthread_cond_broadcast(&cond_) == 0; }

private:
  pthread_cond_t cond_;
  Mutex& mutex_;

  HTTPCOMM_DISABLE_COPY_ASSIGN(Cond);
};

class ScopedLock {
public:
  explicit ScopedLock(Mutex& mutex) : mutex_(mutex),
                                      enable_(true) {
    mutex_.Lock();
  }

  ~ScopedLock() {
    if (enable_) {
      mutex_.Unlock();
    }
  }

  void Disable() {
    enable_ = false;
  }

private:
  Mutex& mutex_;
  bool enable_;

  HTTPCOMM_DISABLE_COPY_ASSIGN(ScopedLock);
};

HTTPCOMM_NAMESPACE_END
