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
      m_cur_token += m_cur_ch;
      m_next_ch = infile.peek();
      this->setType();
      if(std::find(cbegin(m_ends), cend(m_ends), m_cur_type) != cend(m_ends)) {
        this->addToken();
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
    std::cout << "Type: " << (int)node.type << ", Token: {" << node.token << "}" << std::endl;
  }
}

/**
*
*/
void Tokenizer::setType()
{
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
  StringHelper::trim(m_cur_token, " \r\n\t");
  TokenNode node(m_cur_type, m_cur_token);
  m_nodes.push_back(node);
  m_cur_token.clear();
  m_cur_type = TokenType::None;
}
