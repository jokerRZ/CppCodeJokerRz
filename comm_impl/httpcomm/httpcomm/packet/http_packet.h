#pragma once

#include <httpcomm/packet/packet.h>

HTTPCOMM_NAMESPACE_BEGIN

enum HttpMethod {
  HM_NONE,
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

  HttpVersion GetVersion() const { return mVersion; }

  void SetVersion(HttpVersion version);

  bool GetHeader(const std::string& key, std::string* value) const;

  bool AddHeader(const std::string& key, const std::string* value);

  const HeaderMap& GetHeaderMap() const { return mHeaderMap; }

  void SetHeaderMap(const HeaderMap& headerMap) { mHeaderMap = headerMap; }

  const std::vector<char>& GetBody() const { return mBody; }

  void AppendBody(const void* data, size_t len);

  uint32_t GetSerialNumber() const { return mSerialNumber; }

  void SetSerialNumber(uint32_t number) { mSerialNumber = number; }

  bool GetIsKeepAlive() const { return mIsKeepAlive; }

  void SetIsKeepAlive(bool keepAlive) { mIsKeepAlive = keepAlive; }

protected:
  HeaderMap mHeaderMap;
  std::vector<char> mBody;
  HttpVersion mVersion;
  uint32_t mSerialNumber;
  bool mIsKeepAlive;
};

class HttpRequestPacket : public HttpPacket {
private:
  friend class HttpPacketFactory;

  HttpRequestPacket() : mMethod(HM_NONE) {}

  virtual ~HttpRequestPacket() {}

public:
  HttpMethod GetHttpMethod() const { return mMethod; }

  void SetHttpMethod(HttpMethod method) { mMethod = method; }

  const std::string& GetUri() const { return mUri; }

  void SetUri(const std::string& uri) { mUri = uri; }

  bool GetHost(std::string* host) const {
    HeaderMapConstIter it = mHeaderMap.find("host");
    if (it == mHeaderMap.end()) {
      return false;
    }
    *host = it->second;
    return true;
  }

  bool SetHost(const std::string& host) {
    HeaderMapConstIter it = mHeaderMap.find("host");
    if (it != mHeaderMap.end()) {
      return false;
    }
    mHeaderMap["host"] = host;
    return true;
  }

private:
  std::string mUri;
  HttpMethod mMethod;
};

class HttpResponsePacket : public HttpPacket {
private:
  friend class HttpPacketFactory;

  HttpResponsePacket() : mStatusCode(-1) {}

  virtual ~HttpResponsePacket() {}

public:
  int GetStatusCode() const { return mStatusCode; }

  void SetStatusCode(int statusCode);

  const std::string& GetStatus() const { return mStatus; }

  void SetStatus(const std::string* status) { mStatus = status; }

private:
  std::string mStatus;
  int mStatusCode;
};

class HttpPacketFactory {
public:
  static HttpResponsePacket* CreateResponse();
  static HttpRequestPacket* CreateRequest();
};

HTTPCOMM_NAMESPACE_END