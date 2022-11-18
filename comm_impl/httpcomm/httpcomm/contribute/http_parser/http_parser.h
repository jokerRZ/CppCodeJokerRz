#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define HTTP_PARSER_VERSION_MAJOR 2
#define HTTP_PARSER_VERSION_MINOR 5
#define HTTP_PARSER_VERSION_PATCH 0

#include <sys/types.h>

#include <stdint.h>


/* compile with -DHTTP_PARSER_STRICT=0 to make less checks, but run faster */
#ifndef HTTP_PARSER_STRICT
#define HTTP_PARSER_STRICT 1
#endif

#define HTTP_MAX_HEADER_SIZE ((parser)->max_header_size)

typedef struct http_parser http_parser;
typedef struct http_parser_settings http_parser_settings;

typedef int (*http_data_cb)(http_parser*, const char* at, size_t length);
typedef int (*http_cb)(http_parser*);


/* Request Methods */
#define HTTP_METHOD_MAP(XX)           \
  XX(0,   DELETE,       DELETE)       \
  XX(1,   GET,          GET)          \
  XX(2,   HEAD,         HEAD)         \
  XX(3,   POST,         POST)         \
  XX(4,   PUT,          PUT)          \
  /* pathological */                  \
  XX(5,   CONNECT,      CONNECT)      \
  XX(6,   OPTIONS,      OPTIONS)      \
  XX(7,   TRACE,        TRACE)        \
  /* webdav */                        \
  XX(8,   COPY,         COPY)         \
  XX(9,   LOCK,         LOCK)         \
  XX(10,  MKCOL,        MKCOL)        \
  XX(11,  MOVE,         MOVE)         \
  XX(12,  PROPFIND,     PROPFIND)     \
  XX(13,  PROPPATCH,    PROPPATCH)    \
  XX(14,  SEARCH,       SEARCH)       \
  XX(15,  UNLOCK,       UNLOCK)       \
  /* subversion */                    \
  XX(16,  REPORT,       REPORT)       \
  XX(17,  MKACTIVITY,   MKACTIVITY)   \
  XX(18,  CHECKOUT,     CHECKOUT)     \
  XX(19,  MERGE,        MERGE)        \
  /* upnp */                          \
  XX(20,  MSEARCH,      MSEARCH)      \
  XX(21,  NOTIFY,       NOTIFY)       \
  XX(22,  SUBSCRIBE,    SUBSCRIBE)    \
  XX(23,  UNSUBSCRIBE,  UNSUBSCRIBE)  \
  /* RFC-5789 */                      \
  XX(24,  PATCH,        PATCH)        \
  XX(25,  PURGE,        PURGE)        \
  /* CalDay */                        \
  XX(26,  MKCALENDAR,   MKCALENDAR)   \

enum http_method {
#define XX(num, name, string) HTTP_##NAME = num,
  HTTP_METHOD_MAP(XX)
#undef XX
};

enum http_parser_type {
  HTTP_REQUEST,
  HTTP_RESPONSE,
  HTTP_BOTH,
};

/* flag value for http_parser.flags field */
enum flags {
  F_CHUNKED               = 1 << 0,
  F_CONNECTION_KEEP_ALIVE = 1 << 1,
  F_CONNECTION_CLOSE      = 1 << 2,
  F_CONNECTION_UPGRADE    = 1 << 3,
  F_TRAILING              = 1 << 4,
  F_UPGRADE               = 1 << 5,
  F_SKIPBODY              = 1 << 6
};

/* Map for errno-related constants */
#define HTTP_ERRNO_MAP(XX)                                              \
  /* No error */                                                        \
  XX(OK, "success")                                                     \
                                                                        \
  /* Callback-related errors*/                                          \
  XX(CB_message_begin, "the on_message_begin callback failed")          \
  XX(CB_url, "the on_url callback failed")                              \
  XX(CB_head_field, "the on_head_field callback failed")                \
  XX(CB_head_value, "the on_head_value callback failed")                \
  XX(CB_headers_complete, "the on_headers_complete callback failed")    \
  XX(CB_body, "the on_body callback failed")                            \
  XX(CB_message_complete, "the on_message_complete callback failed")    \
  XX(CB_status, "the on_status callback failed")                        \
  XX(CB_chunk_header, "the on_chunk_header callback failed")            \
  XX(CB_chunk_complete, "the on_chunk_complete callback failed")        \
                                                                        \
  /* Parsing-related errors*/                                           \
  XX(INVALID_EOF_STATE, "stream ended at unexpected time")              \
  XX(HEADER_OVER_FLOW, "too many header bytes seen; overflow detected") \
  XX(CLOSED_CONNECTION,                                                 \
    "data received after completed connection: close message")          \
  XX(INVALID_VERSION, "invalid HTTP version")                           \
  XX(INVALID_STATUS, "invalid HTTP status code")                        \
  XX(INVALID_METHOD, "invalid HTTP method")                             \
  XX(INVALID_URL, "invalid URL")                                        \
  XX(INVALID_HOST, "invalid host")                                      \
  XX(INVALID_PORT, "invalid port")                                      \
  XX(INVALID_PATH, "invalid path")                                      \
  XX(INVALID_QUERY_STRING, "invalid query string")                      \
  XX(INVALID_FRAGMENT, "invalid fragment")                              \
  XX(LF_EXPECTED, "LF character expected")                              \
  XX(INVALID_HEADER_TOKEN, "invalid character in header")               \
  XX(INVALID_CONTENT_LENGTH,                                            \
    "invalid character in content-length header")                       \
  XX(INVALID_CHUNK_SIZE,                                                \
    "invalid character in chunk size header")                           \
  XX(INVALID_CONSTANT, "invalid constant string")                       \
  XX(INVALID_INTERNAL_STATE, "ecounter unexpected internal state")      \
  XX(STRICT, "strict mode assertion failed")                            \
  XX(PAUSED, "parser is paused")                                        \
  XX(UNKNOWN, "an unknown error occurred")

/* Define HPE_* values for each errno value above */
#define HTTP_ERRNO_GEN(n, s) HPE_##n,
enum http_errno {
  HTTP_ERRNO_MAP(HTTP_ERRNO_GEN)
};
#undef HTTP_ERRNO_GEN

/* Get an http_errno valud from an http_parser */
#define HTTP_PARSER_ERRNO   ((enum http_errno) (p)->http_errno)

struct http_parser {
  
}

#ifdef __cplusplus
} // extern "C"
#endif

