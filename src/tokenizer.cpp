#include <cstring>
#include <iostream>
#include <fstream>
#include <regex>
#include "tokenizer.h"


void Tokenizer::parse(const std::string& filename)
{
  const char* delimiters = "= ()<>";
  std::ifstream file(filename);
  std::string line;
  bool do_parse = false;
  std::string uuid;

  if(file.is_open()) {
    while(std::getline(file, line)) {
      if(line.starts_with("END:")) {
        do_parse = false;
        return;
      }

      if(do_parse) {
        char* token = std::strtok(line.data(), delimiters);
        while(token) {
          std::cout << token << std::endl;
          token = std::strtok(nullptr, delimiters);
        }
      }
      
      if(line.starts_with("START:")) {
        std::smatch sm;
        if(std::regex_search(line, sm, std::regex(R"(\{{1}(.*)\}{1})"))) {
          uuid = sm[1];
        }
        do_parse = true;
      }

    }
  }
} 
