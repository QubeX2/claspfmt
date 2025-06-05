#include <cstddef>
#include <cstdint>
#include <fstream>
#include <string>
#include <iostream>
#include <filesystem>
#include <cstdio>
#include "writer.h"
#include "helpers.h"

void Writer::put(std::vector<Section> sections, std::string filename)
{
  std::filesystem::path file(filename);
  std::string filepath_html = filename + ".html";
  std::string filepath_out = file.parent_path().string().size() 
      ? file.parent_path().string()  + "/" + file.stem().string() + ".out.asp" 
      : file.stem().string() + ".out.asp";

  std::ifstream htmlfile(filepath_html);
  std::ofstream outfile(filepath_out);

  if(htmlfile.is_open()) {
    std::string line;

    while(std::getline(htmlfile, line, '\n')) {
      size_t fpos = line.find("CLASPFMT", 0);
      while(fpos != std::string::npos) {
        std::string id = line.substr(fpos + 9, 36);
        //line.replace(fpos, 46, "");
        for(auto section: sections) {
          if(id == section.id) {
            std::string content;
            size_t cur_indent = 0;
            for(size_t index = 0; auto secl: section.lines) {
              StringHelper::trim(secl, " ");
              if(secl.size()) {
                content.append(secl);
              }
            }
            //line.insert(fpos, content);
          }
        }
        fpos = line.find("CLASPFMT", fpos + 1);
      }
      outfile << line << "\n";
    }

    htmlfile.close();
    outfile.close();
    std::remove(std::string(filename + ".claf").c_str());
    std::remove(std::string(filename + ".html").c_str());
  }
  
}
