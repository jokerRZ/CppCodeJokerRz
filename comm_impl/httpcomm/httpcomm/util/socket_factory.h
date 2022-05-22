#pragma once

#include <string>

#include <httpcomm/util/tcp_listen_socket.h>
#include <httpcomm/util/tcp_client_socket.h>
#include <httpcomm/util/tcp_server_socket.h>

HTTPCOMM_NAMESPACE_BEGIN

class SocketFactory {
public:
  static TcpListenSocket* CreateTcpListenSocket(const std::string& spec);

  static TcpClientSocket* CreateTcpClientSocket(const std::string& peer,
                                                const std::string& local);

  static TcpServerSocket* CreateTcpServerSocket(int fd, in_addr_t peerAddr,
                                                uint16_t peerPort,
                                                in_addr_t localAddr,
                                                uint16_t localPort);
};

HTTPCOMM_NAMESPACE_END
