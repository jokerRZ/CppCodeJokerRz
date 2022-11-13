#pragma once

#include <cstdint>

#include <httpcomm/util/define.h>

HTTPCOMM_NAMESPACE_BEGIN

template <typename T>
class AtomicIntegerT {
public:
  AtomicIntegerT() : value_(0) {}

  T FetchAndAdd(T x) { return __sync_fetch_and_add(&value_, x); }

  T FetchAndSet(T x) { return __sync_lock_test_and_set(&value_, x); }

  T Get() const { return value_; }

  T AddAndFetch(T x) { return __sync_add_and_fetch(&value_, x); }

  bool CompareAndSet(T old_val, T new_val) {
    return __sync_bool_compare_and_set(&value_, old_val, new_val);
  }

private:
  volatile T value_;
};


typedef AtomicIntegerT<int16_t> AtomicInteger16;
typedef AtomicIntegerT<int32_t> AtomicInteger32;
typedef AtomicIntegerT<int64_t> AtomicInteger64;

typedef AtomicIntegerT<uint16_t> AtomicIntegerU16;
typedef AtomicIntegerT<uint32_t> AtomicIntegerU32;
typedef AtomicIntegerT<uint64_t> AtomicIntegerU64;

HTTPCOMM_NAMESPACE_END
