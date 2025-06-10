#include <cctype>
#include <algorithm>
#include <regex>
#include <string>
#include <variant>
#include "mylib.h"
#include "types.h"
#include "tokenizer.h"

/**
 *
 */
std::string mylib::variant::to_string(const value_t &value)
{
  if(std::holds_alternative<std::string>(value)) {
    return std::get<std::string>(value);
  } else if(std::holds_alternative<double>(value)) {
    return std::to_string(std::get<double>(value));
  } else if(std::holds_alternative<int>(value)) {
    return std::to_string(std::get<int>(value));
  }
  return "";
}

/**
 *
 */
void mylib::variant::append_to(std::string &str, const value_t &value)
{
  str += mylib::variant::to_string(value);
}

/**
 *
 */
void mylib::string::trim(std::string& str, std::string chars)
{
  str.erase(0, str.find_first_not_of(chars));
  str.erase(str.find_last_not_of(chars) + 1);
}

/**
*
*/
bool mylib::string::is_anyof(const char& ch, const std::string& chars)
{
  return std::any_of(
    std::cbegin(chars),
    std::cend(chars),
    [&](const char& c) { return c == ch; }
  );
}

/*
*
*/
std::string mylib::string::tolower(std::string &str)
{
  std::string nstr;
  std::transform(std::begin(str), std::end(str), std::back_inserter(nstr), [](unsigned char c) { return std::tolower(c); });
  return nstr;
}

/**
*
*/
std::string mylib::string::ucfirst(std::string& str)
{
  std::string nstr = mylib::string::tolower(str);
  if(nstr.size()) {
    nstr[0] = std::toupper(str[0]);
  }
  return nstr;
}


/**
*
*/
TokenListItem mylib::token::concat_string(const token_list_t& tokens, uint start, uint length)
{
  std::string result;
  uint i = 0;
  if(start >= 0 && start < tokens.size() && length >= 0 && (length + start) < tokens.size()) {
    for(i = start; i < (start + length); i++) {
      mylib::variant::append_to(result, tokens[i].value);
    }
  }
  return { .string_value = result, .index = (i - start + 1) };
}

/**
*
*/
TokenListItem mylib::token::until_string(const token_list_t& tokens, uint start, std::string end, bool include)
{
  std::string result;
  uint i = 0;
  if(start > 0 && start < tokens.size()) {
    for(i = start; i < tokens.size(); i++) {
      if(mylib::token::concat_string(tokens, i, end.size()).string_value == end) {
        if(include) {
          result += end;
        }
        return { .string_value = result, .index = (i - start + 1) };
      }
      mylib::variant::append_to(result, tokens[i].value);
    }
  }
  return { .string_value = "", .index = 0 };
}

/**
*
*/
TokenListItem mylib::token::until_char(const token_list_t& tokens, uint start, char ch)
{
  std::string result;
  uint i = 0;
  if(start > 0 && start < tokens.size()) {
    for(uint i = start; i < tokens.size(); i++) {
      std::string s = mylib::variant::to_string(tokens[i].value);
      if(s.find(ch) != std::string::npos) {
        return { .string_value = result, .index = (i - start + 1) };
      } else {
        result += s;
      } 
    }
  }
  return { .string_value = "", .index = 0 };
}

/**
*
*/
TokenListItem mylib::token::until_char_is(const token_list_t& tokens, uint start, std::function<int(int)>& comp)
{
  std::string result;
  uint i = 0;
  if(start > 0 && start < tokens.size()) {
    for(uint i = start; i < tokens.size(); i++) {
      std::string s = mylib::variant::to_string(tokens[i].value);
      if(std::any_of(s.begin(), s.end(), [&](unsigned char ch) { return(comp(ch)); })) {
        return { .string_value = result, .index = (i - start + 1) };
      } else {
        result += s;
      } 
    }
  }
  return { .string_value = "", .index = 0 };

}

/**
*
*/
TokenListItem mylib::token::until_regex(const token_list_t& tokens, uint start, uint length, std::string pattern)
{
  std::string result;
  uint i = 0;
  if(start >= 0 && start < tokens.size() && length >= 0 && (length + start) < tokens.size()) {
    for(i = start; i < tokens.size(); i++) {
      if(std::regex_search(mylib::token::concat_string(tokens, i, length).string_value, std::regex(pattern))) {
        return { .string_value = result, .index = (i - start + 1) };
      }
      mylib::variant::append_to(result, tokens[i].value);
    }
  }
  return { .string_value = "", .index = 0 };
}

TokenListItem mylib::token::until_type(const token_list_t& tokens, uint start, TokenType type)
{
  std::string result;
  uint i = 0;
  if(start >= 0 && start < tokens.size()) {
    for(i = start; i < tokens.size(); i++) {
      TokenNode tn = tokens[i];
      if(tn.type == type) {
        return { .string_value = result, .index = (i - start + 1) };
      }
      mylib::variant::append_to(result, tn.value);
    }
  }
  return { .string_value = "", .index = 0 };
}

/**
*
*/
TokenListItem mylib::token::find_first(const token_list_t& tokens, uint start, uint length, std::string search)
{
  uint i = 0;
  if(start >= 0 && start < tokens.size() && length >= 0 && (length + start) < tokens.size()) {
    for(i = start; i < tokens.size(); i++) {
      if(mylib::token::concat_string(tokens, i, length).string_value == search) {
        TokenNode tn = tokens[i];
        return { .token = tn, .string_value = mylib::variant::to_string(tn.value), .index = (i - start + 1) };
      }
    }
  }
  return { .string_value = "", .index = 0 };
}

/**
*
*/
TokenListItem mylib::token::find_first_regex(const token_list_t& tokens, uint start, uint length, std::string pattern)
{
  uint i = 0;
  if(start >= 0 && start < tokens.size() && length >= 0 && (length + start) < tokens.size()) {
    for(i = start; i < tokens.size(); i++) {
      if(std::regex_search(mylib::token::concat_string(tokens, i, length).string_value, std::regex(pattern))) {
        TokenNode tn = tokens[i];
        return { .token = tn, .string_value = mylib::variant::to_string(tn.value), .index = (i - start + 1) };
      }
    }
  }
  return { .string_value = "", .index = 0 };
}

