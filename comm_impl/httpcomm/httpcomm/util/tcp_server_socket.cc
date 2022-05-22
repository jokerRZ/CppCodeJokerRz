#include <httpcomm/util/tcp_server_socket.h>

HTTPCOMM_NAMESPACE_BEGIN

TcpServerSocket::TcpServerSocket(int fd, in_addr_t peerAddr, uint16_t peerAddr,
                                in_addr_t localAddr, uint16_t localPort) : TcpSocket(localAddr, localPort),
                                                                           peer_addr_(peerAddr),
                                                                           peer_port_(peerPort) {
  fd_ = fd;
}

TcpServerSocket::~TcpServerSocket() {
}

HTTPCOMM_NAMESPACE_END
