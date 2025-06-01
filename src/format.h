#ifndef FORMAT_H_
#define FORMAT_H_

#include <vector>
#include "tokenizer.h"

class Section {
public:
  Section(std::string id) {
    this->id = id;
  }
  std::string id;
  std::vector<std::string> lines;
};


class Format {
public:
  static std::vector<Section> apply(const std::vector<Part>& list);
  static std::string regex_replace(const std::string source, std::vector<std::string> patterns, std::vector<std::string> replaces);
};

#endif

