#include <algorithm>
#include <cctype>
#include <iterator>
#include <iostream>
#include <regex>
#include <vector>
#include <cctype>
#include <algorithm>
#include <string>
#include "helpers.h"
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

void Format::indentation(std::string source, int& indent)
{
  StringHelper::trim(source, " <%>");

  if(source.starts_with("'")) {
    return;
  }

  std::vector<std::string> indenter_patterns = { 
    R"(^if.*then([ ]*'.*)?$)",
    R"(^for.*to.+([ ]*'.*)?$)",
    R"(^for.*each.*in.+('.*)?$)",
    R"(^\bdo\b([ ]*'.*)?$)",
    R"(^do while.+('.*)?$)",
    R"(^do until.+('.*)?$)",
  };
  std::vector<std::string> exdenter_patterns = {
    R"(^\bnext\b([ ]*'.*)?$)",
    R"(^\bloop\b([ ]*'.*)?$)",
    R"(^loop while.+('.*)?)",
    R"(^loop until.+('.*)?)",
  };
  std::vector<std::string> indenters = {};
  std::vector<std::string> exdenters = { 
    "end if",
  };

  // indenter patterns
  for(auto pattern: indenter_patterns) {
    if(std::regex_search(source, std::regex(pattern))) {
      indent++;
    }
  }

  // exdenter patterns
  for(auto pattern: exdenter_patterns) {
    if(std::regex_search(source, std::regex(pattern))) {
      indent--;
    }
  }

  // indenters
  for(auto search: indenters) {
    if(source.find(search) != std::string::npos) {
      indent++;
    }
  }

  // exdenters
  for(auto search: exdenters) {
    if(source.find(search) != std::string::npos) {
      indent--;
    }
  }
}

std::vector<Section> Format::apply(const std::vector<Part>& list)
{
  std::vector<Section> sections;
  int indent = 0;
  int old_indent = 0;
  int check = 0;
  for(auto part: list) {
    Section block = Section(part.id); 
    for(auto token: part.tokens) {
      std::string lcase;
      std::transform(token.item.begin(), token.item.end(), std::back_inserter(lcase), [](unsigned char c) { return std::tolower(c); }); 

      // formatting
      std::string line = Format::keywords(token.item);

      // indentation
      check = indent;
      Format::indentation(lcase, indent);
      /*
      if(check == indent) {
        token.item.insert(token.item.begin(), indent, '\t');
      } */
      old_indent = indent;
      std::cout << indent;
      std::cout << token.item << std::endl;

      block.lines.push_back(token.item);
    }
    sections.push_back(block);
  }

  return sections;
}
