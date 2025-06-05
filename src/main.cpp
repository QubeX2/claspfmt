#include <iostream>
#include "tokenizer.h"

int main(int argc, char *argv[]) 
{
  Tokenizer tnz;
  tnz.parseFile(std::string(argv[1]));
  return 0;
}
