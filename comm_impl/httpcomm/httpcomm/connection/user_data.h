#pragma once

#include <httpcomm/common.h>

HTTPCOMM_NAMESPACE_BEGIN

class UserData {
public:
  UserData();

  virtual ~UserData();

  virtual void Free() = 0;
};

HTTPCOMM_NAMESPACE_END