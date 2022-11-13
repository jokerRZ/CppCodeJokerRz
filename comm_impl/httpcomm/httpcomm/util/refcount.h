#pragma once

#include <httpcomm/util/atomic.h>

HTTPCOMM_NAMESPACE_BEGIN

class RefCount {
public:
  int AddRef() { mRefCount.AddAndFetch(1); }

  int Release() {
    int ref = mRefCount.AddAndFetch(-1);
    if (ref == 0) { Free(); }
    return ref;
  }

  int GetRef() const { return mRefCount.Get(); }

protected:
  RefCount() { mRefCount.FetchAndSet(1); }

  virtual ~RefCount() {}

  virtual void Free() { delete this; }
private:
  AtomicInteger32 mRefCount;
};

HTTPCOMM_NAMESPACE_END