#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>

enum class TokenType { Symbol = 1, WhiteSpace };

class Token {
public:
  TokenType type;
  std::string item;

};

class Part {
public:
  std::vector<class Token> tokens;
};

class Tokenizer {
private:
public:
  static void parse(const std::string& filename);
};

#endif
