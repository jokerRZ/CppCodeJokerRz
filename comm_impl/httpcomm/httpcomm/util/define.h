#pragma once

#define HTTPCOMM_NAMESPACE_BEGIN namespace httpcomm {
#define HTTPCOMM_NAMESPACE_END }

#define HTTPCOMM_DISABLE_COPY_ASSIGN(T)         \
  private:                                      \
    T(const T&);                                \
    T& operator=(const T&)

#define HTTPCOMM_DELETE_AND_SET_NULL(x)         \
  do {                                          \
    delete x; x = nullptr;                      \
  } while (0)

#define HTTPCOMM_DELETE_ARRAY_AND_SET_NULL(x)   \
  do {                                          \
    delete[] x; x = nullptr;                    \
  } while (0)
