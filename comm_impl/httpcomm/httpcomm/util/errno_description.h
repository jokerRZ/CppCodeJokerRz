#pragma once

#include <httpcomm/common.h>

HTTPCOMM_NAMESPACE_BEGIN

class ErrnoDescription {
public:
  static const char* GetDescription(int err);
};

HTTPCOMM_NAMESPACE_END
