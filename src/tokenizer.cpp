#include <cctype>
#include <cstdint>
#include <format>
#include <fstream>
#include <iostream> 
#include <regex>
#include <string>
#include <sys/wait.h>
#include <vector>
#include <algorithm>
#include "mylib.h"
#include "types.h"
#include "tokenizer.h"

/**
 *
 */
std::string TokenNode::to_string_value() const
{
  return mylib::variant::to_string(this->value);
}

/**
 *
 */
void Tokenizer::pass2()
{
  uint index = 0;
  std::string cur_str;
  std::string next_str;
  std::string next2_str;
  std::string last_str;
  TokenNode cur_token;
  TokenNode next_token;
  TokenNode next2_token;
  TokenNode last_token;
  WaitingFor waiting_for = WaitingFor::None;
  
  std::string res_str;
  bool added_token = false;
  Lang cur_lang = Lang::None;
  size_t tokens_size = m_pass1_tokens.size();

  for(index = 0; index < tokens_size; index++) {
    added_token = false;
    cur_token = m_pass1_tokens[index];
    if(index > 0) {
      last_token = m_pass1_tokens[index - 1];
      last_str = last_token.to_string_value();
    }
    if(index < tokens_size - 1) {
      next_token = m_pass1_tokens[index + 1];
      next_str = next_token.to_string_value();
    }
    if(index < tokens_size - 2) {
      next2_token = m_pass1_tokens[index + 2];
      next2_str = next2_token.to_string_value();
    }

    cur_str = mylib::variant::to_string(cur_token.value);

    // HtmlTagClose
    if(cur_str == ">" && waiting_for == WaitingFor::HtmlTagStartClose) {
      waiting_for = WaitingFor::None;
      index++;
      this->add_token(m_pass2_tokens, TokenType::HtmlTagStart, ">");
      added_token = true;
    }

    // HtmlAttribute
    //std::cout << std::format("Strings: {}, {}, {}\n", cur_str, next_str, next2_str);
    if(cur_token.type == TokenType::Atom && next_str == "=" && next2_str == "\"" 
      && waiting_for == WaitingFor::HtmlTagStartClose) 
    {
      auto tli_rest = mylib::token::until_char(m_pass1_tokens, index + 3, '"');
      // std::cout << std::format("Rest: {}\n", tli_rest.string_value);
      index += tli_rest.index + 2;
      this->add_token(m_pass2_tokens, TokenType::HtmlAttribute, cur_str + "=\"" + tli_rest.string_value + "\"");
      added_token = true;
    }

    // AspVariable
    if(cur_token.type == TokenType::Atom && next_str == "." && cur_lang == Lang::Asp) {
      waiting_for = WaitingFor::ParenStart;
      index += 2;
      this->add_token(m_pass2_tokens, TokenType::AspVariable, cur_str + next_str + next2_str);
      added_token = true;
    }

    if(cur_str == "(" && waiting_for == WaitingFor::ParenStart && cur_lang == Lang::Asp) {
      waiting_for = WaitingFor::None;
    } else if(waiting_for == WaitingFor::ParenStart) {
      waiting_for = WaitingFor::None;
    }

    // <
    if(cur_str == "<") {
      // HtmlComment
      if((res_str = mylib::token::concat_string(m_pass1_tokens, index, 4).string_value) == "<!--") {
        cur_lang = Lang::Html;
        auto tli_rest = mylib::token::until_string(m_pass1_tokens, index + 4, "-->", true);
        index += tli_rest.index + 5;
        res_str += tli_rest.string_value;
        this->add_token(m_pass2_tokens, TokenType::HtmlComment, res_str);
        added_token = true;
      }

      // HtmlTag
      if(next_token.type == TokenType::Atom) {
        waiting_for = WaitingFor::HtmlTagStartClose;
        std::string end = next2_str == ">" ? ">" : "";
        index += end.length() ? 2 : 1;
        this->add_token(m_pass2_tokens, TokenType::HtmlTagStart, "<" + next_str + end);
        added_token = true;
        if(end.length()) {
          waiting_for = WaitingFor::None;
        }
      }

      // AspTagStart
      if((res_str = mylib::token::concat_string(m_pass1_tokens, index, 2).string_value) == "<%") {
        index += 2;
        cur_lang = Lang::Asp;
        this->add_token(m_pass2_tokens, TokenType::AspTagStart, "<%");
        added_token = true;
      }
    }

    // AspTagEnd
    if(cur_str == "%") {
      if((res_str = mylib::token::concat_string(m_pass1_tokens, index, 2).string_value) == "%>") {
        index += 2;
        cur_lang = Lang::None;
        this->add_token(m_pass2_tokens, TokenType::AspTagEnd, "%>");
        added_token = true;
      }
    }

    // AspComment
    if(cur_str == "'" && cur_lang == Lang::Asp) {
      auto tli_rest = mylib::token::until_char(m_pass1_tokens, index + 1, 10);
      index += tli_rest.index;
      this->add_token(m_pass2_tokens, TokenType::AspComment, "'" + tli_rest.string_value);
      added_token = true;
    }

    // HtmlColor
    /*
    if(cur_str == "#" && std::regex_match(next_str, 
      std::regex("([0-9a-fA-F]{2}[0-9a-fA-F]{2}[0-9a-fA-F]{2}|[0-9a-fA-F]{1}[0-9a-fA-F]{1}[0-9a-fA-F]{1})"))) 
    {
      this->add_token(m_pass2_tokens, TokenType::HtmlColor, "#" + next_str);
      index += 2;
      added_token = true;
    } */

    if(!added_token) {
      m_pass2_tokens.push_back(cur_token);
    }
  }

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
          if(std::regex_match(cur_token, std::regex("[-+]?[0-9]+"))) {
            this->add_token(m_pass1_tokens, TokenType::Number, cur_token);
          } else if(std::all_of(cur_token.begin(), cur_token.end(), [](unsigned char ch) { return std::isalpha(ch); })) {
            this->add_token(m_pass1_tokens, TokenType::Atom, cur_token);
          } else {
            this->add_token(m_pass1_tokens, TokenType::Symbol, cur_token);
          }
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
  // this->print_tokens(m_pass2_tokens);
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

