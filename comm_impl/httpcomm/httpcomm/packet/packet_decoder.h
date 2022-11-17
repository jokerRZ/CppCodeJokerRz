#pragma once

#include <httpcomm/common.h>

HTTPCOMM_NAMESPACE_BEGIN

class Packet;
class PacketDecoder {
protected:
  PacketDecoder() {}
  
  virtual ~PacketDecoder() {}

public:
  virtual bool Decode(const char* buf, size_t len) = 0;

  virtual Packet* GetPacket() = 0;

  virtual void Free() = 0;
};

HTTPCOMM_NAMESPACE_END