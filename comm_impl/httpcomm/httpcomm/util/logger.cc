#include <httpcomm/util/logger.h>

HTTPCOMM_NAMESPACE_BEGIN

namespace {

class DefaultLogger : public Logger {

public:
  DefaultLogger() {}
  virtual ~DefaultLogger() {}

public:
  virtual void Log(Level level,
                   const char* file,
                   int line,
                   const char* fmt, ...) override
  {}
};

DefaultLogger DEFAULT_LOGGER;
Logger* LOGGER = nullptr;

}

Logger& Logger::GetLogger() {
  if (!LOGGER) {
    return DEFAULT_LOGGER;
  }
  return *LOGGER;
}

void Logger::SetLogger(Logger& logger) {
  LOGGER = &logger;
}

void Logger::ResetLogger() {
  LOGGER = nullptr;
}


HTTPCOMM_NAMESPACE_END
