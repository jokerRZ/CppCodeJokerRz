#include <httpcomm/packet/http_packet_encoder.h>

HTTPCOMM_NAMESPACE_BEGIN

namespace {

const std::string CONTENT_LENGTH("content-length");
const std::string CONNECTION("connection");
const std::string KEEPALIVE_HEADER("Connection: Keep-Alive\r\n");
const std::string CONNECTION_CLOSE("Connection: Close\r\n");

typedef HttpPacket::HeaderMap HeaderMap;
typedef HeaderMap::iterator HeaderMapIter;
typedef HeaderMap::const_iterator HeadMapConstIter;

} // namespace

HttpRequestPacketEncoder::HttpRequestPacketEncoder() {}

HttpRequestPacketEncoder::~HttpRequestPacketEncoder() {}

bool HttpRequestPacketEncoder::Encode(const Packet& packet, ByteBuffer* buffer) {
  if (!buffer) return false;

  const HttpRequestPacket* requestPacket = dynamic_cast<const HttpRequestPacket*>(&packet);
  if (!requestPacket) {
    HTTPCOMM_ERROR("bad request packet");
    return false;
  }

  std::string str;
  HttpMethod method = requestPacket->GetHttpMethod();
  switch (method) {
  case HM_GET:
    str += "GET ";
    break;
  case HM_HEAD:
    str += "HEAD ";
    break;
  case HM_POST:
    str += "POST ";
    break;
  case HM_PUT:
    str += "PUT ";
    break;
  case HM_PATCH:
    str += "PATCH ";
    break;
  case HM_DELETE:
    str += "DELETE ";
    break;
  default:
    HTTPCOMM_ERROR("method [%d] is not support", method);
    return false;
  }

  auto const& uri = requestPacket->GetUri();
  if (uri.empty()) {
    HTTPCOMM_ERROR("uri is empty");
    return false;
  }
  str += uri;

  HttpVersion version = requestPacket->GetVersion();
  switch (version) {
  case HV_10:
    str += " HTTP/1.0\r\n";
    break;
  case HV_11:
    str += " HTTP/1.1\r\n";
    break;
  default:
    HTTPCOMM_ERROR("version [%d] is not supported", version);
    return false;
  }

  const HeaderMap& headerMap = requestPacket->GetHeaderMap();
  if (version )


}


HTTPCOMM_NAMESPACE_END