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

#define HTTPCOMM_LOG(level, fmt, args...)         \
  Logger::GetLogger().Log(level, __FILE__, __LINE__, fmt, ##args)

#define HTTPCOMM_DEBUG(fmt, args...)              \
  Logger::GetLogger().Log(Logger::Level::LL_DEBUG, __FILE__, __LINE__, fmt, ##args)

#define HTTPCOMM_TEACE(fmt, args...)              \
  Logger::GetLogger().Log(Logger::Level::LL_TRACE, __FILE__, __LINE__, fmt, ##args)

#define HTTPCOMM_WARNING(fmt, args...)            \
  Logger::GetLogger().Log(Logger::Level::LL_WARNING, __FILE__, __LINE__, fmt, ##args)

#define HTTPCOMM_ERROR(fmt, args...)              \
  Logger::GetLogger().Log(Logger::Level::LL_ERROR, __FILE__, __LINE__, fmt, ##args)

HTTPCOMM_NAMESPACE_END
