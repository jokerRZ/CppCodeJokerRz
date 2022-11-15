#pragma once

#include <httpcomm/common.h>
#include <httpcomm/packet/packet_encoder.h>

HTTPCOMM_NAMESPACE_BEGIN

class PacketEncoderFactory {
public:
  PacketEncoderFactory() {}

  virtual ~PacketEncoderFactory() {}

  virtual PacketEncoder* Create() = 0;

  virtual void Free() = 0;
};

HTTPCOMM_NAMESPACE_END