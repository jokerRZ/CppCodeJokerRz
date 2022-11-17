#pragma once

#include <httpcomm/packet/http_packet.h>
#include <httpcomm/packet/packet_decoder.h>
#include <httpcomm/contribute/http_parser/http_parser.h>

HTTPCOMM_NAMESPACE_BEGIN

class HttpPacketDecoder : public PacketDecoder {
public:
  enum Type {
    HT_NONE,
    HT_REQUEST,
    HT_RESPONSE
  };

  struct ThreshHold {
    size_t _maxUri;
    size_t _maxHeader;
    size_t _maxBody;

    ThreshHode();
  };

  HttpPacketDecoder();

  virtual ~HttpPacketDecoder();

private:
  
};

HTTPCOMM_NAMESPACE_END