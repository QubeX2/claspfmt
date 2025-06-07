#ifndef HELPERS_H
#define HELPERS_H

#include "tokenizer.h"
#include <functional>
#include<string>


class StringHelper {
public:
  static void trim(std::string& str, std::string chars);
  static bool is_anyof(const char& ch, const std::string& chars);
  static std::string tolower(std::string& str);
  static std::string ucfirst(std::string& str);
};

class TokenHelper {
public:
  static TokenListItem concat_string(const token_list_t& tokens, uint start, uint length);
  static TokenListItem until_string(const token_list_t& tokens, uint start, std::string end);
  static TokenListItem until_first_char_is(const token_list_t& tokens, uint start, std::function<int(int)>& comp);
  static TokenListItem until_regex(const token_list_t& tokens, uint start, uint length, std::string pattern);
  static TokenListItem find_first(const token_list_t& tokens, uint start, uint length, std::string search);
  static TokenListItem find_first_regex(const token_list_t& tokens, uint start, uint length, std::string pattern);
};

#endif
