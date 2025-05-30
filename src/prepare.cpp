#include <iostream>
#include <fstream>
#include "prepare.h"

/**
* Prepare the file for prettier formatting
* 1) Remove <%.*%> tags and replace with TAGIDs
* 2) Write ASP code to filename TAGID.claf
* 3) Rename file to {name}.html
*/
void Prepare::run(char* file) const
{
  std::cout << file << std::endl;
  std::ifstream f(file);

  if(!f.is_open()) {
    std::cerr << "Error opening file";
  }

  std::string s;
  while(std::getline(f, s)) {
    std::cout << s << std::endl;
  }
}
