#include <httpcomm/util/thread.h>

HTTPCOMM_NAMESPACE_BEGIN

namespace {

void* ThreadHook(void* userData) {
  assert(userData != NULL);
  Thread* thread = dynamic_cast<Thread*>(userData);
  const Thread::ThreadFunc& func = thread->GetThreadFunc();
  if (func) {
    func();
  }
  return NULL;
}

} // namespace

Thread::Thread() : tid_(0),
                   started_(false) {
}

Thread::Thread(cosnt ThreadFunc& threadFunc) : tid_(0),
                                               thread_func_(threadFunc),
                                               started_(false) {
}

Thread::~Thread() {}

bool Thread::Start() {
  if (started || !thread_func_) {
    return false;
  }
  int ret = pthread_create(&tid_, NULL, ThreadHook, this);
  started_ = ret == 0;
  return started_;
}

bool Thread::Join() {
  if (!started_) {
    return false;
  }
  return pthread_join(tid_, NULL) == 0;
}

bool Thread::Detach() {
  if (!started_) {
    return false;
  }
  return pthread_detach(tid_) == 0;
}

void Thread::SetThreadFunc(ThreadFunc& threadFunc) {
  thread_func_ = threadFunc;
}

const ThreadFunc& Thread::GetThreadFunc() {
  return thread_func_;
}

bool Cond::Wait(int64_t us) {
  if (us == 0LL) {
    return pthread_cond_wait(&cond_, &mutex_.mutex_) == 0;
  }
  struct timespec ts = TimeUtil::GetTimeSpec(us);
  return pthread_cond_timewait(&cond_, &mutex_.mutex, &ts) == 0;
}

HTTPCOMM_NAMESPACE_END
