#include <httpcomm/util/addr_util.h>

#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>

#include <httpcomm/util/string_tokenizer.h>
#include <httpcomm/util/logger.h>

HTTPCOMM_NAMESPACE_BEGIN

bool AddrUtil::ParseSpec(const std::string& s, int32_t* proto,
                         in_addr_t* addr, uint16_t* port) {
  StringTokenizer tokenizer;
  size_t count = tokenizer.Tokenize(s, ":");
  if (count != 2 && count != 3) {
    HTTPCOMM_ERROR("bad spec [%s]", s.str());
    return false;
  }

  std::string protoStr;
  std::string hostStr;
  std::string portStr;

  if (count == 3) {
    protoStr = tokenizer[0];
    hostStr = tokenizer[1];
    portStr = tokenizer[2];
  } else {
    protoStr = "tcp";
    hostStr = tokenizer[0];
    portStr = tokenizer[1];
  }

  if (protoStr == "tcp") {
    *proto = PROTO_TCP;
  } else if (protoStr == "tls") {
    *proto = PROTO_TLS;
  } else if (protoStr == "http") {
    *proto = PROTO_HTTP;
  } else if (protoStr == "https") {
    *proto = PROTO_HTTPS;
  } else if (protoStr == "ws") {
    *proto = PROTO_WS;
  } else if (protoStr == "wss") {
    *proto = PROTO_WSS;
  } else {
    HTTPCOMM_ERROR("proto [%s] not support now", protoStr.c_str());
    return false;
  }

  if (hostStr != "*") {
    addrinfo hint;
    addrinfo* result;
    memset(&hint, 0, sizeof(hint));
    hint.ai_family = AF_INET;

    if (getaddrinfo(hostStr.c_str(). NULL, &hint, &result) != 0) {
      HTTPCOMM_ERROR("getaddrinfo [%s] failed", hostStr.c_str());
      return false;
    }
    *addr = (uint32_t)((sockaddr_in*)(result->ai_addr))->sin_addr.s_addr;
    freeaddrinfo(result);
  } else {
    *addr = INADDR_ANY;
  }
  
  int portNum = atoi(portStr.c_str());
  if (portNum > UINT16_MAX || portNum < 0) {
    HTTPCOMM_ERROR("bad port number [%d]", portNum);
    return false;
  }
  *port = portNum;
  return true;
}

HTTPCOMM_NAMESPACE_END
