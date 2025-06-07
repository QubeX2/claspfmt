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
token_list_t Tokenizer::tokenize(const std::string &filename)
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
          this->add_token(TokenType::Symbol);
        }
        m_cur_token += m_cur_ch;
        this->add_token(std::isspace(m_cur_ch) ? TokenType::Whitespace : TokenType::Token);
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
void Tokenizer::print_tokens()
{
  for(auto node: m_tokens) {
    std::cout << std::format("Type: [{}], Token: |{}|\n", (uint8_t)node.type, node.value);
  }
}

/**
*
*/
void Tokenizer::add_token(TokenType type)
{
  m_tokens.push_back(TokenNode({ .type = type, .value = m_cur_token }));
  m_cur_token.clear();
}

