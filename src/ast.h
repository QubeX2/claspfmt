#ifndef AST_H
#define AST_H

#include "tokenizer.h"
#include <iterator>
#include <memory>
#include <sys/types.h>
#include <vector>

enum class AstLang {
  None = 0,
  Asp,
  JavaScript,
  Html,
};

enum class AstType {
  None = 0,
  Declaration,
  Assignment,
  Function,
  Argument,
  Comment,
};

enum class AstValueType {
  None = 0,
  String, 
  Number,
};

struct AstNode;

using ast_node_t = std::shared_ptr<AstNode>;
using ast_node_w = std::weak_ptr<AstNode>;
using ast_node_list_t = std::vector<ast_node_t>;

struct AstNode {
  ast_node_list_t children;
  ast_node_t parent;
  AstLang lang;
  AstType type;
  std::string value;
  AstValueType value_type;
};



class AstTree {
  token_list_t m_tokens;
  ast_node_t m_tree;

  ast_node_t add_node(ast_node_t parent, std::string value = "", 
                      AstType type = AstType::None,
                      AstValueType value_type = AstValueType::None,
                      AstLang lang = AstLang::None);
public:
  AstTree(token_list_t tokens);
  void parse();
  void print_tree();
};

#endif
