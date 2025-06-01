#include <iostream>
#include <fstream>
#include <string>
#include "prepare.h"
#include "tokenizer.h"
#include "format.h"

int main(int argc, char *argv[]) {
  std::string filename = Prepare::run(std::string(argv[1]));
  if(filename.size()) {
    std::vector<Part> list = Tokenizer::parse(filename + ".claf");
    if(list.size()) {
      std::vector<Section> sections = Format::apply(list);
      std::cout << "Formatted " << sections.size() << " sections" << std::endl;
    }
  }


  return 0;
}
