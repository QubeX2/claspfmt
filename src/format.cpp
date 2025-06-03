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
  return source;
}

void Format::indentation(std::string source, size_t& indent, bool& iskeyword)
{
  StringHelper::trim(source, " <%>");
  iskeyword = false;

  if(source.starts_with("'")) {
    return;
  }

  std::vector<std::string> keyword_patterns = {
    R"(^\belse\b([ ]*'.*)?$)",
  };

  std::vector<std::string> indenter_patterns = { 
    R"(^if.*then([ ]*'.*)?$)",
    R"(^select.+case.+([ ]*'.*)?$)",
    R"(^for.*to.+([ ]*'.*)?$)",
    R"(^for.*each.*in.+('.*)?$)",
    R"(^\bdo\b([ ]*'.*)?$)",
    R"(^do while.+('.*)?$)",
    R"(^do until.+('.*)?$)",
    R"(^function.+('.*)?$)",
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
    "end function",
    "end select",
  };

  // keyword patterns
  for(auto pattern: keyword_patterns) {
    if(std::regex_search(source, std::regex(pattern))) {
      iskeyword = true;
      return;
    }
  }


  // indenter patterns
  for(auto pattern: indenter_patterns) {
    if(std::regex_search(source, std::regex(pattern))) {
      indent++;
      iskeyword = true;
      return;
    }
  }

  // exdenter patterns
  for(auto pattern: exdenter_patterns) {
    if(std::regex_search(source, std::regex(pattern))) {
      indent--;
      return;
    }
  }

  // indenters
  for(auto search: indenters) {
    if(source.find(search) != std::string::npos) {
      indent++;
      iskeyword = true;
      return;
    }
  }

  // exdenters
  for(auto search: exdenters) {
    if(source.find(search) != std::string::npos) {
      indent--;
      return;
    }
  }
}

std::vector<Section> Format::apply(const std::vector<Part>& list)
{
  std::vector<Section> sections;
  size_t indent = 0;
  bool iskeyword = false;
  bool inside_block = false;
  bool should_indent = false;

  for(auto part: list) {
    Section block = Section(part.id); 
    for(auto token: part.tokens) {
      std::string lcase;
      std::transform(token.item.begin(), token.item.end(), std::back_inserter(lcase), [](unsigned char c) { return std::tolower(c); }); 

      // formatting
      std::string line = Format::keywords(token.item);

      // indentation
      Format::indentation(lcase, indent, iskeyword);
      int n = iskeyword ? indent - 1 : indent;

      // HANDLE SELECT CASE ... END SELECT
      if(std::regex_search(lcase, std::regex(R"(^select.+case.+([ ]*'.*)?$)"))) {
        inside_block = true;
      }
      
      if(lcase.find("end select") != std::string::npos) {
        inside_block = false;
        should_indent = false;
      }

      if(should_indent && !lcase.starts_with("case")) {
        n++;
      }
      // END HANDLE SELECT CASE ... END SELECT

      token.item.insert(token.item.begin(), (n > 0 ? n : 0) * 4, ' ');
      
      // HANDLE SELECT CASE ... END SELECT
      if(inside_block && lcase.starts_with("case")) {
        should_indent = true;
      }
      // END HANDLE SELECT CASE ... END SELECT

      // std::cout << token.item << std::endl;

      block.lines.push_back(token.item);
      block.indents.push_back(n);
    }
    sections.push_back(block);
  }

  return sections;
}
