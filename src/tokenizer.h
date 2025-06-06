#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <array>
#include <vector>
#include <span>
#include <iostream>

#define TYPES \
X(None) \
X(Keyword) \
X(AspTagStart) \
X(AspTagEnd) \
X(AspComment) \
X(AspCommentEnd) \
X(HtmlComment) \
X(HtmlCommentEnd) \
X(HtmlTag) \
X(HtmlTagEnd)


#define X(value) value,
enum class TokenType : size_t {
  TYPES
};
#undef X


/*
enum class TokenType : size_t { 
  None = 0, 
  Keyword,

  AspTagStart,
  AspTagEnd,
  AspComment,
  AspCommentEnd,

  HtmlComment,
  HtmlCommentEnd,
  HtmlTag,
  HtmlTagEnd,
}; */

class TokenNode {
public:
  TokenType type;
  std::string token;
};

class Tokenizer {
  const std::array<TokenType, 5> m_ends = { 
    TokenType::HtmlCommentEnd, TokenType::HtmlTagEnd,
    TokenType::AspTagStart, TokenType::AspTagEnd, TokenType::AspCommentEnd 
  };

  const std::array<std::string, 13> m_keywords = {
    "if", "then", "end if", "else", "elseif", // 5 
    "loop", "do while", "not", // 3
    "select case", "case", "end_select" // 3
    "while", "wend" // 2
  };

  std::vector<TokenNode> m_nodes;
  std::string m_filename;
  std::string m_cur_token;
  TokenType m_cur_type = TokenType::None;
  char m_cur_ch = 0;
  char m_next_ch = 0;
  char m_last_ch = 0;

  void addToken();
  void setType();
  void printNodes();
  bool isKeyword(std::string& str);

public:
  void parseFile(const std::string& filename);
};

#endif
