#include <cctype>
#include <cstdint>
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
std::vector<TokenNode> Tokenizer::tokenize(const std::string &filename)
{
  m_filename = filename;
  std::ifstream infile(m_filename);

  if(infile.is_open()) {
    while(infile.get(m_cur_ch)) {
      if(m_cur_ch == 13) { continue; }
      if(std::isalnum(m_cur_ch)) {
        m_cur_token += m_cur_ch;
      } else { 
        if(m_cur_token.size()) {
          this->addToken(TokenType::Symbol);
        }
        m_cur_token += m_cur_ch;
        this->addToken(std::isspace(m_cur_ch) ? TokenType::Whitespace : TokenType::Token);
      } 
    }
    infile.close();
  }
  //this->printTokens();
  return m_tokens;
}

/**
*
*/
void Tokenizer::printTokens()
{
  for(auto node: m_tokens) {
    std::cout << std::format("Type: [{}], Token: |{}|, Int: |{}|\n", (uint8_t)node.type, node.token, (int)node.token[0]);
  }
}

/**
*
*/
void Tokenizer::addToken(TokenType type)
{
  m_tokens.push_back(TokenNode({ .type = type, .token = m_cur_token }));
  m_cur_token.clear();
}

