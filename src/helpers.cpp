#include <cctype>
#include <algorithm>
#include <iterator>
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

