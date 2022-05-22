#pragma once

#include <httpcomm/util/socket.h>

HTTPCOMM_NAMSAPCE_BEGIN

class TcpSocket : public Socket {
public:
  TcpSocket(in_addr_t localAddr, uint16_t localPort);

  virtual ~TcpSocket();

public:
  bool Bind();

  in_addr_t GetLocalAddr() const {
    return local_addr_;
  }

  uint16_t GetLocalPort() const {
    return local_port_;
  }

private:
  in_addr_t local_addr_;
  uint16_t local_port_;

  HTTPCOMM_DISABLE_COPY_ASSIGNMENT(TcpSocket);
};

HTTPCOMM_NAMESPACE_END
