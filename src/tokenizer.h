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
#include <variant>
#include "types.h"

enum class TokenType : uint8_t { 
  None = 0, 
  Whitespace,
  Token,
  Symbol,
  Value,
  HtmlComment,
};

class TokenNode {
public:
  std::string to_string_value() const;
  TokenType type = TokenType::None;
  value_t value;
};

class TokenListItem {
public:
  bool isEmpty() { return index == 0 && string_value == "" && token.type == TokenType::None; };
  TokenNode token;
  std::string string_value = "";
  uint index = 0;
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

  token_list_t m_pass1_tokens;
  token_list_t m_pass2_tokens;
  std::string m_filename;

  void add_token(token_list_t& tokens, TokenType type, std::string value);
  void print_tokens(token_list_t& tokens);
  void pass2();

public:
  token_list_t tokenize(const std::string& filename);
};

#endif
