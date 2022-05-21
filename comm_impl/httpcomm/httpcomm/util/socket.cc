#include <httpcomm/util/socket.h>
#include <unistd.h>
#include <httpcomm/util/logger.h>

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
      HTTPCOMM_ERROR("close fd [%d] failed [%s]", fd_
                      )
    }
  }
}

HTTPCOMM_NAMESPACE_END
