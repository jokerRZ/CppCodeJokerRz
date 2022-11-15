#include <httpcomm/wrapper/http_client.h>

HTTPCOMM_NAMESPACE_BEGIN

class HttpClient::ResponsePromise : public RefCount {
public:
  ResponsePromise() : mCond(mMutex),
                      mHasResponse(false),
                      mHasError(false) {}
  virtual ~ResponseFuture {}

  ResponseFuture* GetFuture() const {
    return new ResponseFuture(*const_cast<ResponsePromise*)(this);
  }

  bool GetAndSwap(Response* resp, std::string* errorMsg) {
    ScopedLock lock(mMutex);
    while (!mHasError && !mHasResponse) {
      mCond.Wait();
    }
    if (mHasResponse) {
      std::swap(resp->_headers, mResponse.headers);
      std::swap(resp->_statusCode, mResponse._statusCode);
      std::swap(resp->_status, mResponse._status);
      std::swap(resp->_body, mResponse._body);
      std::swap(resp->_version, mResponse._version);
    }
    if (mHasError) {
      if (errorMsg != nullptr) {
        errorMsg->swap(mErrorMsg);
      } else {
        CYGNET_ERROR("%s", mErrorMsg.c_str());
      }
    }
    return mHasResponse;
  }

  void SetResponse(HttpResponsePacket* resp) {
    ScopedLock lock(mMutex);
    mResponse._version = HttpVersionToString(resp->GetVersion());
    mResponse._headers = resp->GetHeaderMap();
    mResponse._statusCode = resp->GetStatusCode();
    mResponse._status = resp->GetStatus();
    const std::vector<char>& body = resp->GetBody();
    if (!body.empty()) {
      mResponse._body.assign(&body[0], body.size());
    }
    mHasResponse = true;
    mCond.Signal();
    if (mHandler) {
      mHandler(mResponse, mErrorMsg);
    }

  }

  void SetError(const std::string& errorMsg) {
    ScopedLock lock(mMutex);
    mHasError = True;
    mErrorMsg = errorMsg;
    mCond.Signal();
    if (mHandler) {
      mHandler(mResponse, mErrorMsg);
    }
  }

  void SetResponseHandler(const ResponseHandler& handler) {
    ScopedLock lock(mMutex);
    mHandler = handler;
  }

  std::string HttpVersionToString(HttpVersion version) const {
    switch(version) {
    case HV_10:
      return "HTTP/1.0";
    case HV_11:
      return "HTTP/1.1";
    default:
      return "";
    }
  }
private:
  mutable Mutex mMutex;
  mutable Cond mCond;
  Response mResponse;
  std::string mErrorMsg;
  bool mHasResponse;
  bool mHasError;
  ResponseHandler mHandler;
};

namespace {

class HttpUserData 
} // namespace

HTTPCOMM_NAMESPACE_END