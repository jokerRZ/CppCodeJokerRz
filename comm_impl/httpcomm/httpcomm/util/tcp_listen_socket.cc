#include <httpcomm/util/tcp_listen_server.h>
#include <httpcomm/util/logger.h>
#include <httpcomm/util/errno_description.h>

HTTPCOMM_NAMESPACE_BEGIN

TcpListenSocket::TcpListenSocket(in_addr_t localAddr, uint16_t localPort) :TcpSocket(localAddr, localPort) {
}

TcpListenSocket::~TcpListenSocket() {
}

bool TcpListenSocket::Listen(int backlog) const {
  if (fd_ < 0) {
    HTTPCOMM_ERROR("listen on bad fd [%d]", fd_);
    return false;
  }
  if (listen(fd_, backlog) < 0) {
    HTTPCOMM_ERROR("listen on fd [%d] failed, errno [%d]", fd_, errno);
    return false;
  }
  return true;
}

bool TcpListenSocket::Accept(TcpServerSocket** socket) {
  *socket = NULL;

  if (fd_ < 0) {
    HTTPCOMM_ERROR("accept on bad fd [%d]", fd_);
    return false;
  }
  sockaddr_in addr;
  socklen_t addrlen = sizeof(addr);
  int fd = accept(fd_, reinterpret_cast<sockaddr*>(addr), &addrlen);
  if (fd < 0) {
    if (errno != EAGAIN) {
      HTTPCOMM_ERROR("accept on fd [%d] failed [%s]", fd_,
                      ErrnoDescription::GetDescription(errno))
    }
    return false;
  }

  TcpServerSocket* serverSock = SocketFactory::CreateTcpServerSocket(fd, addr.sin_addr.s_addr, ntohs(addr.sin_port),
                                                                     local_addr_, local_port);
  if (serverSock == NULL) {
    HTTPCOMM_ERROR("create tcp server socket failed");
    close(fd);
    return false;
  }
  *socket = serverSock;
  return true;
}

HTTPCOCMM_NAMESPACE_END
