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

std::string Format::regex_replace(const std::string source, std::vector<std::string> patterns, std::vector<std::string> replaces)
{
  return std::string("k");
}

std::vector<Section> Format::apply(const std::vector<Part>& list)
{
  std::vector<Section> sections;
  int  indent = 0;

  for(auto part: list) {
    Section block = Section(part.id); 
    for(auto token: part.tokens) {
      std::string item;
      std::transform(token.item.begin(), token.item.end(), std::back_inserter(item), [](unsigned char c) { return std::tolower(c); }); 

      // formatting
      std::smatch sm;
      std::regex_match(token.item, sm, std::regex(R"(^if.*)", std::regex_constants::icase));
      if(sm.size()) { token.item = std::regex_replace(token.item, std::regex(R"(if)", std::regex_constants::icase), "If");
        std::vector<std::string> patterns;
        std::vector<std::string> replaces;
        token.item = Format::regex_replace(token.item, patterns, replaces);

        /*
        token.item = std::regex_replace(token.item, std::regex(R"(then)", std::regex_constants::icase), "Then"); // indentation
        token.item = std::regex_replace(token.item, std::regex(R"(not)", std::regex_constants::icase), "Not"); // indentation
        token.item = std::regex_replace(token.item, std::regex(R"(request)", std::regex_constants::icase), "Request"); // indentation
        token.item = std::regex_replace(token.item, std::regex(R"(\.form)", std::regex_constants::icase), ".Form"); // indentation
        */
      }

      if(item.starts_with("if")) {
        std::cout << "token: " << token.item << std::endl;
      }

      block.lines.push_back(token.item);
    }
    sections.push_back(block);
  }

  return sections;
}
