#include <iostream>
#include <fstream>
#include <string>
#include "prepare.h"
#include "tokenizer.h"

int main(int argc, char *argv[]) {
  std::string filename = Prepare::run(std::string(argv[1]));
  if(filename.size()) {
    Tokenizer::parse(filename + ".claf");
  }


  return 0;
}
