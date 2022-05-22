#include <httpcomm/util/tcp_socket.h>

#include <arpa/inet.h>

#include <httpcomm/util/logger.h>
#include <httpcomm/util/errno_description.h>

HTTPCOMM_NAMESPACE_BEGIN

TcpSocket::TcpSocket(in_addr_t localAddr, uint16_t localPort) : local_addr_(localAddr),
                                                                local_port_(localPort) {
}

~TcpSocket() {
}

bool TcpSocket::Bind() {
  if (fd_ < 0) {
    HTTPCOMM_ERROR("bind on bad fd [%d]", fd_);
    return false;
  }

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = local_addr_;
  addr.sin_port = htons(local_port_);

  if (bind(fd_, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0) {
    HTTPCOMM_ERROR("bind on fd [%d] failed [%s]", fd_,
                    ErrnoDescription::GetDescription(errno));
    return false;
  }

  if (local_port_ == 0) {
    socklen_t addrLen = sizeof(addr);
    if (getsockname(fd_, reinterpret_cast<sockaddr*>(addr), &addrLen) < 0) {
      HTTPCOMM_ERROR("getsockname on fd [%d] failed [%s]", fd_,
                      ErrnoDescription::GetDescription(errno));
      return false;
    }
    local_port_ = ntohs(addr.sin_port);
  }
  return true;
}

HTTPCOMM_NAMESPACE_END
