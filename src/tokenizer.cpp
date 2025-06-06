#include <cctype>
#include <format>
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
  bool should_write = true;

  if(infile.is_open()) {
    while(infile.get(m_cur_ch)) {
      should_write = true;

      if((m_cur_type == TokenType::None && StringHelper::isAnyOf(m_cur_ch, " ")) 
        || StringHelper::isAnyOf(m_cur_ch, "\t\r\n")) {
        should_write = false;
      }

      if(should_write) {
        m_cur_token += m_cur_ch;
      } else if(m_cur_type == TokenType::None) {
        m_cur_token.clear();
      }

      m_next_ch = infile.peek();

      if(m_cur_type == TokenType::None && m_cur_mode == LangMode::Asp && this->isAspKeyword(m_cur_token)) {
        m_cur_type = TokenType::Keyword;
        this->addToken();
      } else if(m_cur_mode == LangMode::Html && m_cur_type == TokenType::HtmlEndTag) {
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
    std::cout << std::format("Mode: {}, Type: {}, Token: |{}|\n", (int)node.mode, (int)node.type, node.token);
  }
}

/**
*
*/
void Tokenizer::setType()
{
  if(m_cur_type == TokenType::None 
    && m_cur_ch == '<' && std::isalnum(m_next_ch)) {
    m_cur_type = TokenType::HtmlStartTag;
    this->setLangMode(LangMode::Html);
  }

  if(m_cur_mode == LangMode::Html
    && (m_cur_type == TokenType::HtmlStartTag || m_cur_type == TokenType::HtmlEndTag)
    && m_last_ch != '%'
    && m_cur_ch == '>' 
  ) {
    m_cur_type = (m_cur_type == TokenType::HtmlStartTag) ? TokenType::HtmlStartTagEnd : TokenType::HtmlEndTagEnd;
  }

  if(m_cur_mode == LangMode::Html 
    && m_cur_ch == '/' && m_last_ch == '<' && std::isalnum(m_next_ch)) {
    m_cur_type = TokenType::HtmlEndTag;
  }

  if(m_cur_ch == '\'' && m_cur_token.size() == 1) {
    m_cur_type = TokenType::AspComment;
  }

  if(m_cur_ch == '\n' && m_cur_type == TokenType::AspComment) {
    m_cur_type = TokenType::AspCommentEnd;
  }
 
  if(m_cur_ch == '<' && m_next_ch == '!') {
    m_cur_type = TokenType::HtmlComment;
    this->setLangMode(LangMode::Html);
  }

  if(m_cur_ch == '>' && m_last_ch == '-' && m_cur_type == TokenType::HtmlComment) {
    m_cur_type = TokenType::HtmlCommentEnd;
  }

  if(m_cur_ch == '%' && m_last_ch == '<' && m_next_ch != '=') {
    this->setLangMode(LangMode::Asp);
    m_cur_type = TokenType::AspTagStart;
  }

  if(m_cur_type != TokenType::HtmlStartTagEnd 
    && m_cur_mode == LangMode::Asp && m_cur_ch == '>' && m_last_ch == '%') {
    m_cur_type = TokenType::AspTagEnd;
  } 
}

/**
*
*/
void Tokenizer::addToken()
{
  if(m_cur_type == TokenType::Keyword) {
    m_cur_token = StringHelper::ucfirst(m_cur_token);
  }
  m_nodes.push_back(TokenNode({ m_cur_mode, m_cur_type, m_cur_token}));
  m_cur_token.clear();
  m_cur_type = TokenType::None;
}

/**
*
*/
bool Tokenizer::isAspKeyword(std::string& str)
{
  std::string lcase = StringHelper::tolower(str);
  return lcase.size() && std::find(
    std::cbegin(m_asp_keywords),
    std::cend(m_asp_keywords),
    lcase
  ) != std::cend(m_asp_keywords);
}

/**
*
*/
void Tokenizer::setLangMode(LangMode mode)
{
  m_last_mode = m_cur_mode;
  m_cur_mode = mode;
}

