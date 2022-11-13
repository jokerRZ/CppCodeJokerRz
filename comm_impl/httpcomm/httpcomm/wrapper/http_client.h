#pragma once

#include <httpcomm/common.h>

HTTPCOMM_NAMESPACE_BEGIN

class HttpClient {
public:
  typedef std::map<std::string, std::string> HeaderMap;

  struct Request {
    std::string   _version;
    std::string   _method;
    std::string   _uri;
    HeaderMap     _headers;
    std::string   _body;

    Request() : _version("HTTP/1.1") {}
  };

  struct Response {
    std::string   _version;
    int           _statusCode;
    std::string   _status;
    HeaderMap     _headers;
    std::string   _body;
  
  };

  // ResponseHandler(response, error)
  typedef std::function<void(const Response&, const std::string&)> ResponseHandler;

  class ResponsePromise;
  class ConnectionPool;
  class ResponseFuture {
  public:
    bool GetResponse(Response* resp, std::string* errorMsg) const;
  private:
    ResponsePromise& mPromise;
  };
};

HTTPCOMM_NAMESPACE_END
