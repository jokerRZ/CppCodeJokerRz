#include <httpcomm/util/time_util.h>

HTTPCOMM_NAMESPACE_BEGIN

int64_t TimeUtil::GetTimeSec() {
  struct timeval tval;
  gettimeofday(&tval, NULL);
  return tval.tv_sec;
}

int64_t TimeUtil::GetTimeMs() {
  struct timeval tval;
  gettimeofday(&tval, NULL);
  return tval.tv_sec * 1000LL + tval.tv_usec / 1000;
}

int64_t TimeUtil::GetTimeUs() {
  struct timeval tval;
  gettimeofday(&tval, NULL);
  return tval.tv_sec * 1000000LL + tval.tv_usec;
}

int64_t TimeUtil::GetTimeSpec(int64_t usecOffset) {
  struct timespec tspec;
  int64_t uTime = GetTimeUs() + usecOffset;
  tspec.tv_sec = uTime / 1000000;
  tspec.tv_nsec = (uTime % 1000000) * 1000;
  return tspec;
}

HTTPCOMM_NAMESPACE_END
