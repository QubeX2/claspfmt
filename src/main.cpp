#include <iostream>
#include "tokenizer.h"
#include "ast.h"
#include "types.h"

int main(int argc, char *argv[]) 
{
  Tokenizer tnz;
  auto tokens = tnz.tokenize(std::string(argv[1]));

  AstTree at(tokens);
  at.parse();

  return 0;
}
