#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <cstdint>
#include <string>
#include <array>
#include <map>
#include <sys/types.h>
#include <vector>
#include <span>
#include <iostream>

enum class TokenType : uint8_t { 
  None = 0, 
  Whitespace,
  Token,
  Symbol,
};

class TokenNode {
public:
  TokenType type;
  std::string token;
};

class Tokenizer {
  /*
  const std::array<TokenType, 6> m_ends = { 
    TokenType::HtmlCommentEnd, TokenType::HtmlStartTagEnd, TokenType::HtmlEndTagEnd, // 3
    TokenType::AspTagStart, TokenType::AspTagEnd, TokenType::AspCommentEnd, // 6
  }; */

  /*
  const std::array<std::string, 15> m_asp_keywords = {
    "if", "then", "end if", "else", "elseif", // 5 
    "loop", "do while", "not", // 8
    "select case", "case", "end_select" // 11 
    "while", "wend", // 13
    "response", "request", // 15
  }; */

  std::vector<TokenNode> m_tokens;
  std::string m_filename;
  std::string m_cur_token;
  char m_cur_ch = 0;

  void addToken(TokenType type);
  void printTokens();

public:
  std::vector<TokenNode> tokenize(const std::string& filename);
};

#endif
