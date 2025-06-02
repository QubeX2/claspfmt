#include <cstring>
#include <fstream>
#include <regex>
#include <vector>
#include "tokenizer.h"
#include "format.h"
#include "helpers.h"


std::vector<Part> Tokenizer::parse(const std::string& filename)
{
  const char* delimiters = "\n";
  std::ifstream file(filename);
  std::string line;
  bool do_parse = false;
  std::string uuid;
  Part part;
  std::vector<Part> list;

  if(file.is_open()) {
    while(std::getline(file, line)) {
      if(line.starts_with("END:")) {
        do_parse = false;
        list.push_back(part);
      }

      if(do_parse) {
        StringHelper::trim(line, " \r\n\t");

        char* token = std::strtok(line.data(), delimiters);
        while(token) {
          part.tokens.push_back(Token(std::string(token), TokenType::KeyWord));
          token = std::strtok(nullptr, delimiters);
        }
      }
      
      if(line.starts_with("START:")) {
        std::smatch sm;
        if(std::regex_search(line, sm, std::regex(R"(\{{1}(.*)\}{1})"))) {
          uuid = sm[1];
        }
        part = Part(uuid);
        do_parse = true;
      }

    }
  }
  return list;
} 
