#ifndef HELPERS_H
#define HELPERS_H

#include "tokenizer.h"
#include <functional>
#include<string>

class StringHelper {
public:
  static void trim(std::string& str, std::string chars);
  static bool isAnyOf(const char& ch, const std::string& chars);
  static std::string tolower(std::string& str);
  static std::string ucfirst(std::string& str);
};

class TokenHelper {
public:
  static std::pair<std::string, uint> concat(const std::vector<TokenNode>& tokens, int start, int length);
  static std::pair<std::string, uint> until_string(const std::vector<TokenNode>& tokens, int start, std::string end, bool include_end = false);
  static std::pair<std::string, uint> until_char(const std::vector<TokenNode>& tokens, int start, std::function<int(int)>& comp);
};

#endif
