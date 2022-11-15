#pragma once

#include <httpcomm/common.h>

HTTPCOMM_NAMESPACE_BEGIN

class Connection;
class Acceptor;
class EventLoop;
class Thread;

class Transport {
public:
  struct Config {
    bool _isolateAcceptThread;
    bool _closeExec;
    bool _timeCache;
    uint32_t _rcvBufSize;
    uint32_t _sndBufSize;
    uint32_t _threadNum;
    
  };
};

HTTPCOMM_NAMESPACE_END