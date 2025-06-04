#include <cstddef>
#include <cstdint>
#include <fstream>
#include <string>
#include <iostream>
#include "writer.h"
#include "helpers.h"

void Writer::put(std::vector<Section> sections, std::string filename)
{
  std::ifstream htmlfile(filename + ".html");
  std::ofstream outfile(filename + ".tmp.asp");

  if(htmlfile.is_open()) {
    std::string line;

    while(std::getline(htmlfile, line, '\n')) {
      size_t fpos = line.find("CLASPFMT", 0);
      while(fpos != std::string::npos) {
        std::string id = line.substr(fpos + 9, 36);
        line.replace(fpos, 46, "");
        for(auto section: sections) {
          if(id == section.id) {
            std::string content;
            size_t cur_indent = 0;
            for(size_t index = 0; auto secl: section.lines) {
              // std::cout << "SECL: >>" << secl << "<<" << fpos << std::endl;
              size_t indent = section.indents[index];
              // std::string newline = section.types[index] == 0 ? "" : "\n";
              std::string newline = section.lines.size() == 1 ? "" : "\n";

              if(section.types[index] != 0) {
                secl.insert(secl.begin(), indent * 4, ' ');
              }

              StringHelper::trim(secl, " ");
              if(secl.size()) {
                content.append(secl + newline);
              }
            }
            line.insert(fpos, content);
          }
        }
        fpos = line.find("CLASPFMT", fpos + 1);
      }
      // std::cout << line << "\n";
      outfile << line << "\n";
    }

    htmlfile.close();
    outfile.close();
  }
  
}
