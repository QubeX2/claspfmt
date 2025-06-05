#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>
#include <span>

enum class TokenType { 
  None = 0, 
  HtmlComment,
  HtmlCommentEnd,
  AspTagStart,
  AspTagEnd,
};

class TokenNode {
public:
  TokenType type;
  std::string token;
};

class Tokenizer {
  const std::array<TokenType, 3> m_ends = { 
    TokenType::HtmlCommentEnd, TokenType::AspTagStart, 
    TokenType::AspTagEnd
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

public:
  void parseFile(const std::string& filename);
};

#endif
