#include <cstddef>
#include <iostream>
#include <fstream>
#include <optional>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include "prepare.h"
#include "uuid.h"

/**
* Prepare the file for prettier formatting
* Remove <%.*%> tags and replace with <!-- {uuid} -->
* Write ASP code to filename.claf
* Write HTML code to filename.html
*/
std::string Prepare::run(const std::string& filename)
{
  std::ifstream infile(filename);
  std::ofstream htmlfile(filename + ".pre.html");
  std::ofstream claffile(filename + ".claf");

  if(infile.is_open()) {
    char ch;
    char last_ch;
    bool can_write_html = true;
    std::string uuid = UUID::generate();
    while(infile.get(ch)) {
      if(ch == '<' && infile.peek() == '%') {
        can_write_html = false;
        htmlfile << "CLASPFMT(" << uuid << ")";
        claffile << "\nSTART: {" << uuid << "}\n";
      }

      if(can_write_html) {
        htmlfile << ch;
      } else {
        claffile << ch;
      }

      if(ch == '>' && last_ch == '%') {
        can_write_html = true;
        claffile << "\nEND: {" << uuid << "}\n";
        // generate a new uuid
        uuid = UUID::generate();
      }

      last_ch = ch;
    }
    infile.close();
    htmlfile.close();
    claffile.close();

    // run prettier
    std::array<std::string, 3> cmds = {
      "cd $(dirname \"" + filename + "\") && prettier $(basename \"" + filename + ".pre.html\") --write --print-width 250 --no-bracket-spacing --html-whitespace-sensitivity ignore",
      "cd $(dirname " + filename + ") && awk 'NF' $(basename " + filename + ".pre.html)" + " > $(basename " + filename + ".html)",
      "rm " + filename + ".pre.html",
    };

    for(auto cmd: cmds) {
      if(system(cmd.c_str()) != 0) {
        return "";
      }
    }
  } else {
    std::cerr << "Error opening file";
    return "";
  }

  return filename.data();
}
