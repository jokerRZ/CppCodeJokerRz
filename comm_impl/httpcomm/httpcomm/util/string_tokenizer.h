#pragma once

#include <cassert>
#include <string>
#include <vector>
#include <httpcomm/util/define.h>

HTTPCOMM_NAMESPACE_BEGIN

class StringTokenizer {
public:
  enum Option {
    TOKEN_IGNORE_EMPTY = 1,
    TOKEN_TRIM = 2,
    TOKEN_LEAVE_AS = 4,
    TOKEN_TO_LOWER = 8,
  };

  typedef std::vector<std::string> TokenVector;
  typedef TokenVector::const_iterator TokenVectorConstIter;

public:
  StringTokenizer();

  ~StringTokenizer();

  size_t Tokenize(const std::string& str, const std::string& sep,
                  int opt = TOKEN_LEAVE_AS);

  TokenVectorConstIter Begin() const { return tokens_.begin(); }

  TokenVectorConstIter End() const { return tokens_.end(); }

  const std::string& operator[](size_t index) const;

  size_t GetTokenCount() const { return tokens_.size(); }

  const TokenVector& GetTokenVector() const { return tokens_; }

private:
  bool IsSpace(char ch) const { return (ch > 0 && std::isspace(ch)); }

  void AddToken(const std::string& token, int opt);

private:
  TokenVector tokens_;

  HTTPCOMM_DISABLE_COPY_ASSIGN(StringTokenizer);
};

HTTPCOMM_NAMESPACE_END

