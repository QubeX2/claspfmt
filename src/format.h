#ifndef FORMAT_H_
#define FORMAT_H_

#include <cstdint>
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
  std::vector<size_t> indents;
  std::vector<uint8_t> types;
};


class Format {
public:
  static std::vector<Section> apply(const std::vector<Part>& list);
  static std::string& trim(std::string& str);
  static std::string keywords(std::string source);
  static void indentation(std::string source, size_t& indent, bool& iskeyword, uint8_t& type);
};

#endif

