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
  if (version == HV_11) {
    if (!requestPacket->GetIsKeepAlive()) {
      // user's response to add close header when connection close
      if (headerMap.find(CONNECTION) == headerMap.end()) {
        str += CONNECTION_CLOSE;
      } else {
        // user's response to add close header
      }
    } else {
      // keep alive user's response to remove close header
    }
  } else if (version == HV_10) {
    if (requestPacket->GetIsKeepAlive()) {
      if (headerMap.find(CONNECTION) == headerMap.end()) {
        str += KEEPALIVE_HEADER;
      } else {
        // user's response to add keep-alive header
      }
    } else {
      // user's response to remove keep-alive header
    }
  }

  for (auto iter = headerMap.begin(); iter != headerMap.end(); ++iter) {
    str += iter->first + ": " + iter->second + "\r\n";
  }

  auto const& body = requestPacket->GetBody();
  if (!body.empty()) {
    if (headerMap.find(CONTENT_LENGTH) == headerMap.end()) {
      str += CONTENT_LENGTH + ": " + std::to_string(body.size()) + "\r\n";
    }
  }
  str += "\r\n";

  buffer->Append(str.c_str(), str.size());
  if (!body.empty()) {
    buffer->Append(&body[0], body.size());
  }
  return true;
}

void HttpRequestPacketEncoder::Free() {
  delete this;
}

HttpResponsePacketEncoder::HttpResponsePacketEncoder() {}

HttpResponsePacketEncoder::~HttpResponsePacketEncoder() {}

bool HttpResponsePacketEncoder::Encode(const Packet& packet, ByteBuffer* buff) {
  if (!buffer) return false;

  const HttpResponsePacket* responsePacket = dynamic_cast<const HttpResponsePacket*>(&packet);
  if (!responsePacket) {
    HTTPCOMM_ERROR("bad response packet");
    return false;
  }

  std::string str;
  HttpVersion version = responsePacket->GetVersion();
  switch (version) {
  case HV_10:
    str += "HTTP/1.0 ";
    break;
  case HV_11:
    str += "HTTP/1.1 ";
    break;
  default:
    HTTPCOMM_ERROR("version [%d] is not supported", version);
    return false;
  }

  int statusCode = responsePacket->GetStatusCode();
  if (statusCode < 0) {
    HTTPCOMM_ERROR("bad status [%d]", statusCode);
    return false;
  }

  auto const& status = responsePacket->GetStatus();
  if (status.empty()) {
    HTTPCOMM_ERROR("status is empty");
    return false;
  }

  str += std::to_string(statusCode) + " " + status + "\r\n";

  auto const& headerMap = responsePacket->GetHeader();
  if (version == HV_11) {
    if (!responsePacket->GetIsKeepAlive()) {
      if (headerMap.find(CONNECTION) == headerMap.end()) {
        str += CONECTION_CLOSE;
      } else {
        // user's response to add close header
      }
    } else {
      // user's response to remove close header
    }
  } else if (version == HV_10) {
    if (responsePacket->GetIsKeepAlive()) {
      if (headerMap.find(CONNECTION) == headerMap.end()) {
        str += KEEPALIVE_HEADER;
      } else {
        // user's response to add keep-alive header
      }
    } else {
      // user's response to response to remove keep-alive header
    }
  }

  for (HeaderMapConstIter iter = headMap.begin(); iter != headerMap.end(); ++iter) {
    str += iter->first + ": " + iter->second + "\r\n";
  }

  auto const& body = responsePacket->GetBody();
  if (headerMap->find(CONTENT_LENGTH) == headerMap.end()) {
    str += CONTENT_LENGTH + ": " + std::to_string(body.size());
  }
  str += "\r\n";

  buffer->Append(str.c_str(); str.size());
  if (!body.empty()) {
    buffer->Append(&body[0], body.size());
  }
  return true;
}

void HttpResponsePacketEncoder::Free() {
  delete this;
}

HTTPCOMM_NAMESPACE_END