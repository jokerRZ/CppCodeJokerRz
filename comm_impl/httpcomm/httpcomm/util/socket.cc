#include <httpcomm/util/socket.h>
#include <unistd.h>
#include <httpcomm/util/logger.h>
#include <httpcomm/util/errno_description.h>

HTTPCOMM_NAMESPACE_BEGIN

Socket::Socket() : fd_(-1) {
}

Socket::~Socket() {
  Close();
}

Socket::Read(void* buf, size_t len) const {
  if (fd_ < 0) {
    HTTPCOMM_ERROR("bad fd [%d]", fd_);
    return -1;
  }

  int n = 0;
  while (true) {
    n = read(fd_, buf, len);
    if (n < 0) {
      if (errno == EINTR) {
        continue;
      }
    }
    break;
  }
  return n;
}

Socket::Write(const void* buf, size_t len) const {
  if (fd_ < 0) {
    HTTPCOMM_ERROR("bad fd [%d]", fd_);
    return -1;
  }

  int n = 0;
  while (true) {
    n = write(fd_, buf, len);
    if (n < 0) {
      if (errno == EINTR) {
        continue;
      }
    }
    break;
  }
  return n;
}

void Socket::Close() {
  if (fd_ >= 0) {
    if (close(fd_) < 0) {
      HTTPCOMM_ERROR("close fd [%d] failed [%s]", fd_,
                     ErrnoDescription::GetDescription(errno));
    }
    fd_ = -1;
  }
}

void Socket::ShutDownWrite() {
  if (fd_ >= 0) {
    shutdown(fd_, SHUT_WR);
  }
}

void Socket::ShutDownRead() {
  if (fd_ >= 0) {
    shutdown(fd_, SHUT_RD);
  }
}

bool Socket::SetNonBlocking(bool enable) const {
  if (fd_ < 0) {
    HTTPCOMM_ERROR("bad fd [%d]", fd_);
    return false;
  }

  int flags = 0;
  if ((flags = fcntl(fd_, F_GETFL)) == -1) {
    HTTPCOMM_ERROR("fcntl fd [%d] F_GETFL failed [%s]", fd_,
                    ErrnoDescription::GetDescription(errno));
    return false;
  }
  if (enable) {
    flags |= O_NONBLOCK;
  } else {
    flags &= ~O_NONBLOCK;
  }
  if (fcntl(fd_, F_SETFL, flags) == -1) {
    HTTPCOMM_ERROR("fcntl fd [%d] F_SETFL failed [%s]", fd_,
                    ErrnoDescription::GetDescription(errno));
    return false;
  }
  return true;
}

bool Socket::SetCloseExec(bool enable) const {
  if (fd_ < 0) {
    HTTPCOMM_ERROR("bad fd [%d]", fd_);
    return false;
  }

  int flags = 0;
  if ((flags = fcntl(fd_, F_GETFL)) == -1) {
    HTTPCOMM_ERROR("fcntl fd [%d] F_GETFL failed [%s]", fd_,
                    ErrnoDescription::GetDescription(errno));
    return false;
  }
  if (enable) {
    flags |= FD_CLOEXEC;
  } else {
    flags &= ~FD_CLOEXEC;
  }
  if (fcntl(fd_, F_SETFL, flags) == -1) {
    HTTPCOMM_ERROR("fcntl fd [%d] F_SETFL failed [%s]", fd_,
                    ErrnoDescription::GetDescription(errno));
    return false;
  }
  return true;

}

bool Socket::SetTcpNoDelay(bool enable) const {
  if (fd_ < 0) {
    HTTPCOMM_ERROR("bad fd [%d]", fd_);
    return false;
  }
  int noDelay = enable ? 1 : 0;
  if (setsocketopt(fd_, IPPROTO_TCP, TCP_NODELAY, &noDelay, sizeof(noDelay)) < 0) {
    HTTPCOMM_ERROR("setsockopt failed on fd [%d]", fd_,
                    ErrnoDescription::GetDescription(errno));
    return false;
  }
  return true;
}

bool Socket::SetSoLinger(bool enable, int seconds) {
  if (fd_ < 0) {
    HTTPCOMM_ERROR("bad fd [%d]", fd_);
    return false;
  }

  struct linger lingerValue;
  lingerValue.l_onoff = enable ? 1 : 0;
  lingerValue.l_linger = seconds;

  if (setsockopt(fd_, SOL_SOCKET, SO_LINGER, &lingerValue, sizeof(lingerValue)) < 0) {
    HTTPCOMM_ERROR("setsockopt failed on fd[%d] [%s]", fd_,
                    ErrnoDescription::GetDescription(errno));
    return false;
  }
  return true;
}

bool Socket::SetTcpKeepAlive(int idleTime, int keepInterval, int cnt) const {
  if (fd_ < 0) {
    HTTPCOMM_ERROR("bad fd [%d]", fd_);
    return false;
  }

  if (setsockopt(fd_, SOL_TCP, TCP_KEEPIDLE, &idleTime, sizeof(idleTime)) < 0) {
    HTTPCOMM
  }
}

HTTPCOMM_NAMESPACE_END
