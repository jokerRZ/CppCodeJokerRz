#pragma once

#include <httpcomm/util/define.h>

HTTPCOMM_NAMESPACE_BEGIN

class Logger {

public:
  enum Level {
    LL_DEBUG,
    LL_TRACE,
    LL_WARNING,
    LL_ERROR
  };

public:
  static Logger& GetLogger();

  static void SetLogger(Logger& logger);

  static void ResetLogger();

protected:
  Logger() {}

  virtual ~Logger() {}

public:
  virtual void Log(Level level,
                   const char* file,
                   int line,
                   const char* fmt, ...) = 0;
};

#define HTTPCOMM_LOG(level, fmt, args...)

HTTPCOMM_NAMESPACE_END
