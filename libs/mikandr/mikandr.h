#ifndef MIKANDR_H
#define MIKANDR_H

#include <functional>
#include <string>
#include "src/tree.h"

namespace mikandr::string {
  void trim(std::string& str, const std::string chars);
  bool is_anyof(const char& ch, const std::string& chars);
  std::string tolower(std::string& str);
  std::string ucfirst(std::string& str);
}

#endif
