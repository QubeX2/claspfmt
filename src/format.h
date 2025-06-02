#ifndef FORMAT_H_
#define FORMAT_H_

#include <vector>
#include "tokenizer.h"

class Language {
public:
  static const std::vector<std::string> keywords ;
};

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
  static std::string& trim(std::string& str);
  static std::string keywords(std::string source);
  static void indentation(std::string source, int& indent);
};

#endif

