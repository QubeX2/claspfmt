#include "ast.h"
#include "helpers.h"
#include "tokenizer.h"
#include <algorithm>
#include <functional>
#include <vector>

void AstTree::parse()
{
  std::string cur_str;
  std::pair<std::string, uint> result;

  for(uint index = 0; index < m_tokens.size(); index++) {
    cur_str = m_tokens[index].token;
    std::cout << cur_str << std::endl;
    //next_str = m_tokens[std::clamp((uint)(index + 1), (uint)0, (uint)(m_tokens.size() - 1))].token;

    if(cur_str == "<") {
      // HtmlComment
      if((result = TokenHelper::concat(m_tokens, index, 4)).first == "<!--") {
        auto rest = TokenHelper::until_string(m_tokens, index + result.first.size() - 1, "-->", true);
        index +=  result.second + rest.second - 1;
      }
    }
  }
  
}


