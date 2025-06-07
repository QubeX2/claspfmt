#ifndef AST_H
#define AST_H

#include "tokenizer.h"
#include <iterator>
#include <sys/types.h>
#include <vector>

enum class AstType {
  None = 0,
  Declaration,
  Assignment,
  Function,
  Argument,
};

enum class AstValueType {
  None = 0,
  String, 
  Number,
};

class AstNode {
  std::vector<AstNode> children;
  std::string name;
  AstType type;
  std::string value;
  AstValueType valueType;
  
};

class AstTree {
  std::vector<TokenNode> m_tokens;
  AstNode m_tree;

public:
  AstTree(std::vector<TokenNode> tokens) : m_tokens{tokens} {};
  void parse();
};

#endif
