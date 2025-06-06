#ifndef HELPERS_H
#define HELPERS_H

#include<string>

class StringHelper {
public:
  static void trim(std::string& str, std::string chars);
  static bool isAnyOf(const char& ch, const std::string& chars);
};

#endif
