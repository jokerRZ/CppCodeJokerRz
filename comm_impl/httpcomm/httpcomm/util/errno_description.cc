#include <httpcomm/util/errno_description.h>

HTTPCOMM_NAMESPACE_BEGIN

namespace {
__thread char ERROR_BUF[256];
}

const char* ErrnoDescription::GetDescription(int err) {
  ERROR_BUF[0] = '\0';
  return strerror_r(err, ERROR_BUF, 256);
}

HTTPCOMM_NAMESPACE_END
