#pragma once

#include <httpcomm/util/tcp_socket.h>

HTTPCOMM_NAMESPACE_BEGIN

class TcpClinetSocket : public TcpSocket {
public:
  TcpClientSocket(in_addr_t peerAddr, uint16_t peerPort,
                  in_addr_t localAddr, uint16_t localPort);

  virtual ~TcpClientSocket();

public:
  // 0 -- connected
  // 1 -- connecting
  // -1 -- error
  int Connect() const;

  in_addr_t GetPeerAddr() const {
    return peer_addr_;
  }

  uint16_t GetPeerPort() const {
    return peer_port_;
  }

protected:
  in_addr_t peer_addr_;
  uint16_t peer_port_;

  HTTPCOMM_DISABLE_COPY_ASSIGN(TcpClientSocket);
};

HTTPCOMM_NAMESPACE_END
