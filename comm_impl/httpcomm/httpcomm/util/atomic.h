#pragma once

#include <cstdint>

#include <httpcomm/util/define.h>

HTTPCOMM_NAMESPACE_BEGIN

template <typename T>
class AtomicIntegerT {
public:
  AtomicIntegerT() : value_(0) {}

  T FetchAndAdd(T x) { return __sync_fetch_and_add(&value_, x); }

private:
  volatile T value_;
};

HTTPCOMM_NAMESPACE_END
