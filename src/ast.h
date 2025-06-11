#ifndef AST_H
#define AST_H

#include "tokenizer.h"
#include "types.h"
#include <iterator>
#include <memory>
#include <sys/types.h>
#include <vector>
#include "mikandr.h"

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

class AstNode : mikandr::tree::INode {
public:
  AstLang lang;
  AstType type;
  value_t value;
  AstValueType value_type;
};



class AstTree {
  token_list_t m_tokens;
  ast_node_t m_tree;

public:
  AstTree(token_list_t tokens);
  void parse();
  void print_tree();
};

#endif
