#ifndef TYPES_H
#define TYPES_H

#include <variant>
#include <string>
#include <vector>

enum class Lang {
  None = 0,
  Html,
  JavaScript,
  Asp,
};

class TokenNode;
struct AstNode;

using token_list_t = std::vector<TokenNode>;
using value_t = std::variant<std::string, int, double>;
using ast_node_t = std::shared_ptr<AstNode>;
using ast_node_w = std::weak_ptr<AstNode>;
using ast_node_list_t = std::vector<ast_node_t>;


#endif
