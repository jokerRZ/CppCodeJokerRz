#include <httpcomm/util/socket_factory.h>

#include <httpcomm/util/addr_util.h>
#include <httpcomm/util/logger.h>
#include <httpcomm/util/errno_description.h>

HTTPCOMM_NAMESPACE_BEGIN

TcpListenSocket* SocketFactory::CreateTcpListenSocket(const std::string& spec) {
  int32_t proto = -1;
  in_addr_t addr = 0;
  uint16_t port = 0;

  if (!AddrUtil::ParseSpec(spec, &proto, &addr, &port)) {
    HTTPCOMM_ERROR("parse spec [%s] failed", spec.c_str());
    return NULL;
  }

  switch (proto) {
  case AddrUtil::PROTO_TCP:
  case AddrUtil::PROTO_HTTP:
  case AddrUtil::PROTO_HTTPS:
  case AddrUtil::PROTO_WS:
  case AddrUtil::PROTO_WSS:
    break;
  default:
    HTTPCOMM_ERROR("proto not support now");
    return NULL;
  }

  int fd = socket(AF_INET, SOCKET_STREAM, 0);
  if (fd < 0) {
    HTTPCOMM_ERROR("create socket failed [%s], spec[%s]"
                   ErrnoDescription::GetDescription(errno), spec.c_str());
    return NULL;
  }

  TcpListenSocket* socket = new TcpListenSocket(addr, port);
  socket->fd_ = fd;

  int enable = 1;
  if (!socket->SetOption(SO_REUSEADDR, &enable, sizeof(enable))) {
    HTTPCOMM_ERROR("set SO_REUSEADDR failed, spec [%s]", spec.c_str());
  }

  if (!socket->Bind()) {
    HTTPCOMM_ERROR("bind failed, spec [%s]", spec.c_str());
    return NULL;
  }

  return socket;
}



HTTPCOMM_NAMESPACE_END
