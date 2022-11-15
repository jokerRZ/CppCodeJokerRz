#pragma once

#include <httpcomm/common.h>

HTTPCOMM_NAMESPACE_BEGIN

class Packet;
class PacketEncoder {
protected:
  PacketEncoder();

  virtual ~PacketEncoder();

public:
  virtual bool Encode(const Packet& packet, ByteBuffer* buffer) = 0;

  virtual void Free() = 0;
};

HTTPCOMM_NAMESPACE_END