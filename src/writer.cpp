
#include "writer.h"
#include <cstddef>
#include <fstream>
#include <string>
#include <iostream>

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
              content.append(secl);
              cur_indent = section.indents[index];
            }
            line.insert(fpos, content);
          }
        }
        fpos = line.find("CLASPFMT", 0);
      }
      std::cout << line << "\n";
    }

    htmlfile.close();
    outfile.close();
  }
  
}
