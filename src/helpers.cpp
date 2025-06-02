#include "helpers.h"

void StringHelper::trim(std::string& str, std::string chars)
{
  str.erase(0, str.find_first_not_of(chars));
  str.erase(str.find_last_not_of(chars) + 1);
}
