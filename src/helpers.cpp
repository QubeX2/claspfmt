#include <cctype>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include "helpers.h"

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
bool StringHelper::isAnyOf(const char& ch, const std::string& chars)
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
std::pair<std::string, uint> TokenHelper::concat(const std::vector<TokenNode>& tokens, int start, int length)
{
  std::string result;
  uint i = 0;
  if(start >= 0 && start < tokens.size() && length >= 0 && (length + start) < tokens.size()) {
    for(i = start; i < (start + length); i++) {
      result += tokens[i].token;
    }
  }
  return { result, (i - start + 1) };
}

/**
*
*/
std::pair<std::string, uint> TokenHelper::until_string(const std::vector<TokenNode>& tokens, int start, std::string end, bool include_end)
{
  std::string result;
  uint i = 0;
  if(start > 0 && start < tokens.size()) {
    for(i = start; i < tokens.size(); i++) {
      if(TokenHelper::concat(tokens, i, end.size()).first == end) {
        if(include_end) {
          result += end;
        }
        return { result, (i - start + 1) };
      }
      result += tokens[i].token;
    }
  }
  return { result, 0 };
}

/**
*
*/
std::pair<std::string, uint> TokenHelper::until_char(const std::vector<TokenNode>& tokens, int start, std::function<int(int)>& comp)
{
  std::string result;
  uint i = 0;
  if(start > 0 && start < tokens.size()) {
    for(uint i = start; i < tokens.size(); i++) {
      if(comp(tokens[i].token[0])) {
        return { result, (i - start + 1) };
      } else {
        result += tokens[i].token;
      }
    }
  }
  return { result, 0 };

}

