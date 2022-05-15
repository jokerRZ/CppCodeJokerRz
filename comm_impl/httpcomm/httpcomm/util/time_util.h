#pragma once

#include <sys/time.h>
#include <cstdint>
#include <httpcomm/util/define.h>

HTTPCOMM_NAMESPACE_BEGIN

class TimeUtil 
public:
  static int64_t GetTimeSec();

  static int64_t GetTimeMs();

  static int64_t GetTimeUs();

  static int64_t GetTimeSpec(int64_t usecOffset);
};

HTTPCOMM_NAMESPACE_END
