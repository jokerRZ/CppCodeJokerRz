#include <httpcomm/util/string_tokenizer.h>

HTTPCOMM_NAMESPACE_BEGIN

StringTokenizer::StringTokenizer() {
}

StringTokenizer::~StringTokenizer() {
}

const std::string& StringTokenizer::operator[](size_t index) const {
  assert(index < tokens_.size());
  return tokens_[index];
}

size_t StringTokenizer::Tokenize(const std::string& str, const std::string& sep,
                                 int opt /* = TOKEN_LEAVE_AS*/) {
  size_t n = 0, old = 0;
  while (n != std::string::npos) {
    n = str.find(sep, n);
    if (n != std::string::npos) {
      if (n != old) {
        AddToken(str.substr(old, n - old), opt);
      } else {
        AddToken("", opt);
      }
      n += sep.length();
      old = n;
    }
  }
  AddToken(str.substr(old, str.length() - old), opt);
  return tokens_.size();
}

void StringTokenizer::AddToken(const std::string& token, int opt) {

  size_t origin_size = tokens_.size();
  size_t length = token.size();
  if (opt & TOKEN_LEAVE_AS) {
    if (!(opt & TOKEN_IGNORE_EMPTY)) {
      tokens_.push_back(token);
    } else if (length > 0) {
      tokens_.push_back(token);
    }
  } else if (opt & TOKEN_TRIM) {
    size_t n = 0;
    while (n < length && IsSpace(token[n])) {
      ++n;
    }
    size_t n2 = length - 1;
    while (n2 >= n && IsSpace(token[n2])) {
      --n2;
    }
    if (n2 >= n) {
      tokens_.push_back(token.substr(n, n2 - n + 1));
    } else if (!(opt & TOKEN_IGNORE_EMPTY)) {
      tokens_.push_back("");
    }
  } else if (length > 0) {
    tokens_.push_back(token);
  }
  if (origin_size < tokens_.size() && (opt & TOKEN_TO_LOWER)) {
    std::string& last_token = tokens_back();
    std::transform(last_token.begin(), last_token.end(), last_token.begin(), std::tolower);
  }
}

HTTPCOMM_NAMESPACE_END
