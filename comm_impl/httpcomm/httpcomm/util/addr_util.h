#pragma once

#include <cstdint>
#include <string>

#include <httpcomm/util/define.h>

HTTPCOMM_NAMESPACE_BEGIN

class AddrUtil {
public:
  static const int32_t PROTO_TCP = 1;
  static const int32_t PROTO_TLS = 2;
  static const int32_t PROTO_HTTP = 3;
  static const int32_t PROTO_HTTPS = 4;
  static const int32_t PROTO_WS = 5;
  static const int32_t PROTO_WSS = 6;

  static bool ParseSpec(const std::string& s, int32_t* proto, in_addr_t* addr,
                        uint16_t* port);
};

HTTPCOMM_NAMESPACE_END
