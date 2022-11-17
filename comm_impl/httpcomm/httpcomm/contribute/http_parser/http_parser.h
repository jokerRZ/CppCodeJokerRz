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
  /* No error */
  XX(OK, )

#ifdef __cplusplus
} // extern "C"
#endif

