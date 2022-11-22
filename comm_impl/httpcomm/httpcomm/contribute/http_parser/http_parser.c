#include "http_parser.h"





#define CURRENT_STATE() p_state

#define UPDATE_STATE(V) p_state = (enum state) (V)

enum state {
  s_dead = 1,           /* import that this is > 0 */
  s_start_req_or_res,
  s_req_or_resp_H,
  s_start_res,
  s_res_H,
  s_res_HT,
  s_res_HTT,
  s_res_HTTP,
  s_res_first_http_major,
  s_res_http_major,
  s_res_first_http_minor,
  s_res_http_minor,
  s_res_first_status_code,
  s_res_status_code,
  s_res_status_start,
  s_res_status,
  s_res_line_almost_done,

  s_start_req,

  s_req_method,

  s_body_identity_eof
};

#define PARSING_HEADER(state) (state <= s_headers_done)


size_t http_parser_execute(http_parser* parser,
                           const http_parser_settings* settings,
                           const char* data,
                           size_t len) {
  char c, ch;
  int8_t unhex_val;
  const char* p = data;
  const char* header_field_mark = NULL;
  const char* header_value_mark = NULL;
  const char* url_mark = NULL;
  const char* body_mark = NULL;
  const char* status_mark = NULL;
  enum state p_state = (enum state)parser->state;

  if (HTTP_PARSER_ERRNO(parser) != HPE_OK) {
    return 0;
  }

  if (len == 0) {
    switch (CURRENT_STATE()) {
      case s_body_identity_eof:
    }
  }
}