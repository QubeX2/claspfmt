#include "ast.h"
#include "mylib.h"
#include "tokenizer.h"
#include "types.h"
#include <algorithm>
#include <functional>
#include <memory>
#include <vector>
#include "mikandr.h"

AstTree::AstTree(token_list_t tokens)
{
  m_tokens = tokens;
  m_tree = std::make_unique<AstNode>();
  m_tree->value = "root";
}

ast_node_t AstTree::add_node(ast_node_t parent, value_t value, AstType type, AstValueType value_type, AstLang lang)
{
  auto an = std::make_shared<AstNode>();
  an->parent = parent;
  an->lang = lang;
  an->type = type;
  an->value_type = value_type;
  an->value = value;
  parent->children.push_back(an);
  return an;
}


void AstTree::parse()
{
  std::string cur_str;
  TokenListItem result;

  mikandr::treenode<std::shared_ptr<AstNode>> tnode;

  /*
  this->add_node(m_tree, "A");
  this->add_node(m_tree, "B");

  for(auto t: m_tree->children) {
    // std::cout << std::format("Value: {}, Parent.Value: {}\n", t->value, t->parent->value);
  } */

  return;
  for(uint index = 0; index < m_tokens.size(); index++) {
    cur_str = mylib::variant::to_string(m_tokens[index].value);
    //std::cout << cur_str << std::endl;

    TokenListItem tli = mylib::token::concat_string(m_tokens, index, 4);
    std::cout << std::format("SV: {}\n", tli.string_value);
    return;
    //next_str = m_tokens[std::clamp((uint)(index + 1), (uint)0, (uint)(m_tokens.size() - 1))].token;

    /*
    if(cur_str == "<") {
      // HtmlComment
      if((result = TokenHelper::concat_string(m_tokens, index, 4)).value == "<!--") {
        auto rest = TokenHelper::until_string(m_tokens, index + result.value.size() - 1, "-->");
        index +=  result.index + rest.index - 1;
      }
    } */
  }

}


