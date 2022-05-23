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
}

void StringTokenizer::AddToken(const std::string& token, int opt) {
  
}

HTTPCOMM_NAMESPACE_END
