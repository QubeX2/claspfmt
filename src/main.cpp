#include <iostream>
#include <fstream>
#include "prepare.h"

int main(int argc, char *argv[]) {
  Prepare p;

  p.run(argv[1]);

  return 0;
}
