#pragma once

#include <httpcomm/util/tcp_socket.h>
#include <httpcomm/util/tcp_server_socket.h>

HTTPCOMM_NAMESPACE_BEGIN

class TcpListenSocket : public TcpSocket {
protected:
  friend class SocketFactory;

  TcpListenSocket(in_addr_t localAddr, uint16_t localPort);

  virtual ~TcpListenSocket();

public:
  bool Listen(int backlog) const;

  bool Accept(TcpServerSocket** socket) const;

  HTTPCOMM_DISABLE_COPY_ASSIGN(TcpListenSocket);
};

HTTPCOMM_NAMESPACE_END
