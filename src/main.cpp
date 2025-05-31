#include <iostream>
#include <fstream>
#include <string>
#include "prepare.h"

int main(int argc, char *argv[]) {
  std::string filename = Prepare::run(std::string(argv[1]));

  return 0;
}
