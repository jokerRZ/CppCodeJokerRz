#pragma once

#include <httpcomm/common.h>

HTTPCOMM_NAMESPACE_BEGIN

class Packet {
protected:
  Packet();

  virtual ~Packet();

public:
  virtual void Free() = 0;

  virtual IsCmdPacket() const = 0;
}

HTTPCOMM_NAMESPACE_END