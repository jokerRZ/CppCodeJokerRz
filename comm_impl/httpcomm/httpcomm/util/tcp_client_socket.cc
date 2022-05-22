#include <httpcomm/util/tcp_client_socket.h>
#include <httpcomm/util/logger.h>
#include <httpcomm/util/errno_description.h>

HTTPCOMM_NAMESPACE_BEGIN

TcpClientSocket(in_addr_t peerAddr, uint16_t peerPort,
                in_addr_t localAddr, uint16_t localPort) : TcpSocket(localAddr, localPort),
                                                           peer_addr_(peer_addr_),
                                                           peer_port_(peer_port_) {
}

TcpClientSocket::~TcpClientSocket() {
}

int TcpClientSocket::Connect() const {
  if (fd_ < 0) {
    HTTPCOMM_ERROR("connect on bad fd [%d]", fd_);
    return false;
  }

  sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = peer_addr_;
  addr.sin_port = htons(peer_port_);

  int rc = 0;
  if (connect(fd_, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0) {
    if (errno != EINPROCESS) {
      HTTPCOMM_ERROR("connect failed on fd [%d]", fd_,
                      ErrnoDescription::GetDescription(errno));
      rc = -1;
    } else {
      rc = 1;
    }
  }
  return rc;
}

HTTPCOMM_NAMESPACE_END
