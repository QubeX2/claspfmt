#include <fstream>
#include <iostream> 
#include <string>
#include <vector>
#include <algorithm>
#include "helpers.h"
#include "tokenizer.h"

/**
 *
 */
void Tokenizer::parseFile(const std::string &filename)
{
  m_filename = filename;
  std::ifstream infile(m_filename);

  if(infile.is_open()) {
    while(infile.get(m_cur_ch)) {

      if(!StringHelper::isAnyOf(m_cur_ch, " \t\r\n")) {
        m_cur_token += m_cur_ch;
      } else if(m_cur_type == TokenType::None) {
        m_cur_token.clear();
      }

      m_next_ch = infile.peek();

      if(m_cur_type == TokenType::None && this->isKeyword(m_cur_token)) {
        m_cur_type = TokenType::Keyword;
        this->addToken();
      } else {
        this->setType();
        if(std::find(cbegin(m_ends), cend(m_ends), m_cur_type) != cend(m_ends)) {
          this->addToken();
        }
      }

      // store last_ch
      m_last_ch = m_cur_ch;
    }
    infile.close();
  }
  this->printNodes();
}

/**
*
*/
void Tokenizer::printNodes()
{
  for(auto node: m_nodes) {
    std::cout << std::format("Type: {}, Token: {}\n", (int)node.type, node.token);
  }
}

/**
*
*/
void Tokenizer::setType()
{
  if(m_cur_ch == '\'' && m_cur_token.size() == 1) {
    m_cur_type = TokenType::AspComment;
  }

  if(m_cur_ch == '\n' && m_cur_type == TokenType::AspComment) {
    m_cur_type = TokenType::AspCommentEnd;
  }
 
  if(m_cur_ch == '<' && m_next_ch == '!') 
    m_cur_type = TokenType::HtmlComment;

  if(m_cur_ch == '>' && m_last_ch == '-' && m_cur_type == TokenType::HtmlComment) 
    m_cur_type = TokenType::HtmlCommentEnd;

  if(m_cur_ch == '%' && m_last_ch == '<')
    m_cur_type = TokenType::AspTagStart;
}

/**
*
*/
void Tokenizer::addToken()
{
  m_nodes.push_back(TokenNode({ m_cur_type, m_cur_token}));
  m_cur_token.clear();
  m_cur_type = TokenType::None;
}

/**
*
*/
bool Tokenizer::isKeyword(std::string& str)
{
  std::cout << std::format("isKeyword: {}\n", str);
  return str.size() && std::find(
    std::cbegin(m_keywords),
    std::cend(m_keywords),
    str
  ) != std::cend(m_keywords);
}

