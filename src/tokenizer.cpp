#include <cctype>
#include <cstdint>
#include <format>
#include <fstream>
#include <iostream> 
#include <string>
#include <vector>
#include <algorithm>
#include "mikandr.h"
#include "types.h"
#include "tokenizer.h"

/**
 *
 */
std::string TokenNode::to_string_value() const
{
  return mikandr::variant::to_string(this->value);
}

/**
 *
 */
void Tokenizer::pass2()
{
  uint index = 0;
  std::string cur_str;
  TokenNode cur_token;
  
  std::string res_str;
  bool added_token = false;

  for(index = 0; index < m_pass1_tokens.size(); index++) {
    added_token = false;
    cur_token = m_pass1_tokens[index];
    cur_str = mikandr::variant::to_string(cur_token.value);
    // std::cout << std::format("Current Token: |{}|\n", cur_str);

    if(cur_str == "<") {
      // HtmlComment
      if((res_str = mikandr::token::concat_string(m_pass1_tokens, index, 4).string_value) == "<!--") {
        auto tli_rest = mikandr::token::until_string(m_pass1_tokens, index + 4, "-->", true);
        index += tli_rest.index + 5;
        res_str += tli_rest.string_value;
        std::cout << std::format("Add Token: |{}|\n", res_str);
        this->add_token(m_pass2_tokens, TokenType::HtmlComment, res_str);
        added_token = true;
      }
    }

    if(!added_token) {
      m_pass2_tokens.push_back(cur_token);
    }
  }
  this->print_tokens(m_pass2_tokens);

}

/**
 *
 */
token_list_t Tokenizer::tokenize(const std::string &filename)
{
  m_filename = filename;
  std::ifstream infile(m_filename);
  std::string cur_token;
  char cur_ch;

  if(infile.is_open()) {
    while(infile.get(cur_ch)) {
      if(cur_ch == 13) { continue; }
      if(std::isalnum(cur_ch)) {
        cur_token += cur_ch;
      } else { 
        if(cur_token.size()) {
          this->add_token(m_pass1_tokens, TokenType::Symbol, cur_token);
          cur_token.clear();
        }
        cur_token += cur_ch;
        this->add_token(m_pass1_tokens, std::isspace(cur_ch) ? TokenType::Whitespace : TokenType::Token, cur_token);
        cur_token.clear();
      } 
    }
    infile.close();
  }
  this->pass2();
  this->print_tokens(m_pass2_tokens);
  return m_pass2_tokens;
}

/**
*
*/
void Tokenizer::print_tokens(token_list_t& tokens)
{
  for(auto node: tokens) {
    std::cout << std::format("Type: [{}], Token: |{}|\n", (uint8_t)node.type, node.to_string_value());
  }
}

/**
*
*/
void Tokenizer::add_token(token_list_t& tokens, TokenType type, std::string value)
{
  tokens.push_back(TokenNode({ .type = type, .value = value }));
}

