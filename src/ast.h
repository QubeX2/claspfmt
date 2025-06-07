#ifndef AST_H
#define AST_H

#include "tokenizer.h"
#include <iterator>
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


class AstNode;

using ast_list_t = std::vector<AstNode>;

class AstNode {
  ast_list_t children;
  AstLang lang;
  AstType type;
  std::string value;
  AstValueType valueType;
  
};


class AstTree {
  token_list_t m_tokens;
  AstNode m_tree;

  void add_node(AstNode& parent);
public:
  AstTree(token_list_t tokens) : m_tokens{tokens} {};
  void parse();
  void print_tree();
};

#endif
