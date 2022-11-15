#pragma once

#include <httpcomm/packet/http_packet.h>
#include <httpcomm/packet/packet_encoder.h>

HTTPCOMM_NAMESPACE_BEGIN

class HttpRequestPacketEncoder : public PacketEncoder {
public:
  HttpRequestPacketEncoder();

  virtual ~HttpRequestPacketEncoder();

  virtual bool Encode(const Packet& packet, ByteBuffer* buff) override;

  virtual void Free() override;
};

// response do not support chunked at now
class HttpResponsePacketEncoder : public PacketEncoder {
public:
  HttpResponsePacketEncoder();
  
  virtual ~HttpResponsePacketEncoder();

  virtual bool Encode(const Packet& packet, ByteBuffer* buff) override;

  virtual void Free() override;
};

HTTPCOMM_NAMESPACE_END