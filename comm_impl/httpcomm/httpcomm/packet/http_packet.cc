#include <httpcomm/packet/http_packet.h>

HTTPCOMM_NAMESPACE_BEGIN

namespace {

class BuiltinHttpStatus {
private:
  struct Status {
    int _code;
    const char* _description;
  };

public:
  static bool Get(int code, std::string* description) {
    if (!description) {
      return false;
    }

    int i = 0;
    while (true) {
      Status* status = mStatus[i++];
      if (!status->_description) {
        break;
      }
      if (code == status->_code) {
        description = status->_description;
        return true;
      }
    }
    return false;
  }

private:
  static Status mStatus[];
};

BuiltinHttpStatus::Status BuiltinHttpStatus::mStatus[] = {
  {200, "OK"},
  {201, "Created"},
  {202, "Acceptor"},
  {204, "No Content"},
  {206, "Partial Content"},
  {301, "Moved Permanently"},
  {302, "Moved Temorarily"},
  {303, "See Other"},
  {304, "Not Modified"}
}

} // namespace

HTTPCOMM_NAMESPACE_END