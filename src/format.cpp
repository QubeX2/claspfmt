#include <algorithm>
#include <cctype>
#include <iterator>
#include <iostream>
#include <regex>
#include <vector>
#include <cctype>
#include <algorithm>
#include <string>
#include "tokenizer.h"
#include "format.h"

const std::vector<std::string> Language::keywords = { 
  "if", "end if", "then", "elseif", "else", "response", "request",
  "for", "to", "next", "step", "exit", "each", "in",
  "do", "while", "loop", "until",
  "select case", "case", "end select",
};

std::string Format::keywords(std::string source)
{
  for(auto& k: Language::keywords) {
  }
  /*
  token.item = std::regex_replace(token.item, std::regex(R"(then)", std::regex_constants::icase), "Then"); // indentation
  token.item = std::regex_replace(token.item, std::regex(R"(not)", std::regex_constants::icase), "Not"); // indentation
  token.item = std::regex_replace(token.item, std::regex(R"(request)", std::regex_constants::icase), "Request"); // indentation
  token.item = std::regex_replace(token.item, std::regex(R"(\.form)", std::regex_constants::icase), ".Form"); // indentation
  */
  return source;
}

void Format::indentation(std::string& source, int& indent)
{
  std::vector<std::string> indenter_patterns = { R"(if.*then)" };
  std::vector<std::string> exdenter_patterns = {};
  std::vector<std::string> indenters = {};
  std::vector<std::string> exdenters = { "else", "elseif", "endif" };

  for(auto pattern: indenter_patterns) {
    if(std::regex_search(source, std::regex(pattern))) {
      indent++;
    }
  }
}

std::vector<Section> Format::apply(const std::vector<Part>& list)
{
  std::vector<Section> sections;
  int indent = 0;

  for(auto part: list) {
    Section block = Section(part.id); 
    for(auto token: part.tokens) {
      std::string lcase;
      std::transform(token.item.begin(), token.item.end(), std::back_inserter(lcase), [](unsigned char c) { return std::tolower(c); }); 

      // formatting
      std::string line = Format::keywords(token.item);

      // indentation
      Format::indentation(lcase, indent);
      std::cout << "Indentation: " << indent << std::endl;

      block.lines.push_back(token.item);
    }
    sections.push_back(block);
  }

  return sections;
}
