#ifndef HELPERS_H
#define HELPERS_H

#include<string>

class StringHelper {
public:
  static void trim(std::string& str, std::string chars);
  static bool isAnyOf(const char& ch, const std::string& chars);
  static std::string tolower(std::string& str);
  static std::string ucfirst(std::string& str);
};

#endif
