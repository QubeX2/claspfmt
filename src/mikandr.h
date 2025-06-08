#ifndef HELPERS_H
#define HELPERS_H

#include "tokenizer.h"
#include "types.h"
#include <functional>
#include<string>

namespace mikandr::string {
  void trim(std::string& str, const std::string chars);
  bool is_anyof(const char& ch, const std::string& chars);
  std::string tolower(std::string& str);
  std::string ucfirst(std::string& str);
}

namespace mikandr::token {
  TokenListItem concat_string(const token_list_t& tokens, uint start, uint length);
  TokenListItem until_string(const token_list_t& tokens, uint start, std::string end, bool include = false);
  TokenListItem until_first_char_is(const token_list_t& tokens, uint start, std::function<int(int)>& comp);
  TokenListItem until_regex(const token_list_t& tokens, uint start, uint length, std::string pattern);
  TokenListItem find_first(const token_list_t& tokens, uint start, uint length, std::string search);
  TokenListItem find_first_regex(const token_list_t& tokens, uint start, uint length, std::string pattern);
}

namespace mikandr::variant {
  std::string to_string(const value_t& value);
  void append_to(std::string& str, const value_t& value);
}
#endif
