#pragma once

#include <httpcomm/util/tcp_socket.h>

HTTPCOMM_NAMESPACE_BEGIN

class TcpServerSocket : public TcpSocket {
protected:
  friend class SocketFactory;

  TcpServerSocket(int fd, in_addr_t peerAddr, uint16_t peerAddr,
                  in_addr_t localAddr, uint16_t localPort);
  virtual ~TcpServerSocket();

public:
  in_addr_t GetPeerAddr() const {
    return peer_addr_;
  }

  uint16_t GetPeerPort() const {
    return peer_port_;
  }

private:
  in_addr_t peer_addr_;
  uint16_t peer_port_;

  HTTPCOMM_DISABLE_COPY_ASSIGN(TcpServerSocket);
};

HTTPCOMM_NAMESPACE_END
