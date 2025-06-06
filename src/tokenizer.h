#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <array>
#include <vector>
#include <span>
#include <iostream>

enum class TokenType : size_t { 
  None = 0, 
  Keyword = 1,
  AspTagStart = 2,
  AspTagEnd = 3,
  AspComment = 4,
  AspCommentEnd = 5,
  HtmlComment = 6,
  HtmlCommentEnd = 7,
  HtmlStartTag = 8,
  HtmlStartTagEnd = 9,
  HtmlEndTag = 10,
  HtmlEndTagEnd = 11,
  HtmlText = 12,
};

enum class LangMode: size_t {
  None = 0,
  JavaScript = 1,
  Html = 2,
  Asp = 3,
};

class TokenNode {
public:
  LangMode mode;
  TokenType type;
  std::string token;
};

class Tokenizer {
  const std::array<TokenType, 6> m_ends = { 
    TokenType::HtmlCommentEnd, TokenType::HtmlStartTagEnd, TokenType::HtmlEndTagEnd, // 3
    TokenType::AspTagStart, TokenType::AspTagEnd, TokenType::AspCommentEnd, // 6
  };

  const std::array<std::string, 15> m_asp_keywords = {
    "if", "then", "end if", "else", "elseif", // 5 
    "loop", "do while", "not", // 8
    "select case", "case", "end_select" // 11 
    "while", "wend", // 13
    "response", "request", // 15
  };

  std::vector<TokenNode> m_nodes;
  std::string m_filename;
  std::string m_cur_token;
  TokenType m_cur_type = TokenType::None;
  LangMode m_cur_mode = LangMode::None;
  LangMode m_last_mode = LangMode::None;
  char m_cur_ch = 0;
  char m_next_ch = 0;
  char m_last_ch = 0;

  void addToken();
  void setType();
  void printNodes();
  bool isAspKeyword(std::string& str);
  void setLangMode(LangMode mode);

public:
  void parseFile(const std::string& filename);
};

#endif
