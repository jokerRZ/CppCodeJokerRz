#pragma once

#include <sys/type.h>

#include <httpcomm/util/define.h>

HTTPCOMM_NAMESPACE_BEGIN

class Socket {
public:
  Socket();

  virtual ~Socket();

  int GetFd() const {
    return fd_;
  }

  int Read(void* buf, size_t len) const;

  int Write(const void* buf, size_t len) const;

  void Close();

  void ShutDownWrite();

  void ShutDownRead();

  bool SetNonBlocking(bool enable) const;

  bool SetCloseExec(bool enable) const;

  bool SetTcpNoDelay(bool enable) const;

  bool SetSoLinger(bool enable, int seconds) const;

  bool SetTcpKeepAlive(int idleTime, int keepInterval, int cnt) const;

  bool SetSoRcvBuf(int buffSize) const;

  bool SetSoSndBuf(int buffSize) const;

  bool SetOption(int option, const void* value, size_t len) const;

  bool GetSoError(int* code) const;

  virtual void Free();

protected:
  int fd_;

  HTTPCOMM_DISABLE_COPY_ASSIGN(Socket);
};

HTTPCOMM_NAMESPACE_END
