#pragma once

#include <httpcomm/packet/packet.h>

HTTPCOMM_NAMESPACE_BEGIN

enum HttpMethod {
  HM_None,
  HM_GET,
  HM_HEAD,
  HM_POST,
  HM_PUT,
  HM_CONNECT,
  HM_PATCH,
  HM_DELETE,
  HM_OTHER,
};

enum HttpVersion {
  HV_NONE,
  HV_10,
  HV_11,
};

class HttpPacket : public Packet {
public:
  friend class HttpPacketDecoder;
  typedef std::map<std::string, std::string> HeaderMap;
  typedef HeaderMap::iterator HeaderMapIter;
  typedef HeaderMap::const_iterator HeaderMapConstIter;

protected:
  HttpPacket();

  virtual ~HttpPacket();

public:
  virtual void Free() { delete this; }

  virtual bool IsCmdPacket() const { return false; }

  HttpVersion GetVersion() const { return m}


private:
  
};

HTTPCOMM_NAMESPACE_END