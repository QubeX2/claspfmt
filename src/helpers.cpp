#include <cctype>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <regex>
#include <string>
#include "helpers.h"
#include "tokenizer.h"

/**
 *
 */
void StringHelper::trim(std::string& str, std::string chars)
{
  str.erase(0, str.find_first_not_of(chars));
  str.erase(str.find_last_not_of(chars) + 1);
}

/**
*
*/
bool StringHelper::is_anyof(const char& ch, const std::string& chars)
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
std::string StringHelper::tolower(std::string &str)
{
  std::string nstr;
  std::transform(std::begin(str), std::end(str), std::back_inserter(nstr), [](unsigned char c) { return std::tolower(c); });
  return nstr;
}

/**
*
*/
std::string StringHelper::ucfirst(std::string& str)
{
  std::string nstr = StringHelper::tolower(str);
  if(nstr.size()) {
    nstr[0] = std::toupper(str[0]);
  }
  return nstr;
}


/**
*
*/
TokenListItem TokenHelper::concat_string(const token_list_t& tokens, uint start, uint length)
{
  std::string result;
  uint i = 0;
  if(start >= 0 && start < tokens.size() && length >= 0 && (length + start) < tokens.size()) {
    for(i = start; i < (start + length); i++) {
      result += tokens[i].value;
    }
  }
  return { .value = result, .index = (i - start + 1) };
}

/**
*
*/
TokenListItem TokenHelper::until_string(const token_list_t& tokens, uint start, std::string end)
{
  std::string result;
  uint i = 0;
  if(start > 0 && start < tokens.size()) {
    for(i = start; i < tokens.size(); i++) {
      if(TokenHelper::concat_string(tokens, i, end.size()).value == end) {
        return { .value = result, .index = (i - start + 1) };
      }
      result += tokens[i].value;
    }
  }
  return { .value = "", .index = 0 };
}

/**
*
*/
TokenListItem TokenHelper::until_first_char_is(const token_list_t& tokens, uint start, std::function<int(int)>& comp)
{
  std::string result;
  uint i = 0;
  if(start > 0 && start < tokens.size()) {
    for(uint i = start; i < tokens.size(); i++) {
      if(comp(tokens[i].value[0])) {
        return { .value = result, .index = (i - start + 1) };
      } else {
        result += tokens[i].value;
      }
    }
  }
  return { .value = "", .index = 0 };

}

/**
*
*/
TokenListItem TokenHelper::until_regex(const token_list_t& tokens, uint start, uint length, std::string pattern)
{
  std::string result;
  uint i = 0;
  if(start >= 0 && start < tokens.size() && length >= 0 && (length + start) < tokens.size()) {
    for(i = start; i < tokens.size(); i++) {
      if(std::regex_search(TokenHelper::concat_string(tokens, i, length).value, std::regex(pattern))) {
        return { .value = result, .index = (i - start + 1) };
      }
      result += tokens[i].value;
    }
  }
  return { .value = "", .index = 0 };
}

/**
*
*/
TokenListItem TokenHelper::find_first(const token_list_t& tokens, uint start, uint length, std::string search)
{
  uint i = 0;
  if(start >= 0 && start < tokens.size() && length >= 0 && (length + start) < tokens.size()) {
    for(i = start; i < tokens.size(); i++) {
      if(TokenHelper::concat_string(tokens, i, length).value == search) {
        TokenNode tn = tokens[i];
        return { .token = tn, .value = tn.value, .index = (i - start + 1) };
      }
    }
  }
  return { .value = "", .index = 0 };
}

/**
*
*/
TokenListItem TokenHelper::find_first_regex(const token_list_t& tokens, uint start, uint length, std::string pattern)
{
  uint i = 0;
  if(start >= 0 && start < tokens.size() && length >= 0 && (length + start) < tokens.size()) {
    for(i = start; i < tokens.size(); i++) {
      if(std::regex_search(TokenHelper::concat_string(tokens, i, length).value, std::regex(pattern))) {
        TokenNode tn = tokens[i];
        return { .token = tn, .value = tn.value, .index = (i - start + 1) };
      }
    }
  }
  return { .value = "", .index = 0 };
}

