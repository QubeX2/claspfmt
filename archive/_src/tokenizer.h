#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>

enum class TokenType { None = 0, KeyWord, Value, WhiteSpace };

class Token {
public:
  Token(std::string s, TokenType t) {
    this->item = s;
    this->type = t;
  }
  TokenType type;
  std::string item;
};

class Part {
public:
  Part() {};
  Part(std::string id) {
    this->id = id;
  }
  std::string id;
  std::vector<class Token> tokens;
};

class Tokenizer {
private:
public:
  static std::vector<Part> parse(const std::string& filename);
};

#endif
