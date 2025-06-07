#include "ast.h"
#include "helpers.h"
#include "tokenizer.h"
#include <algorithm>
#include <functional>
#include <vector>

void AstTree::parse()
{
  std::string cur_str;
  TokenListItem result;

  for(uint index = 0; index < m_tokens.size(); index++) {
    cur_str = m_tokens[index].value;
    std::cout << cur_str << std::endl;
    
    //next_str = m_tokens[std::clamp((uint)(index + 1), (uint)0, (uint)(m_tokens.size() - 1))].token;

    if(cur_str == "<") {
      // HtmlComment
      if((result = TokenHelper::concat_string(m_tokens, index, 4)).value == "<!--") {
        auto rest = TokenHelper::until_string(m_tokens, index + result.value.size() - 1, "-->");
        index +=  result.index + rest.index - 1;
      }
    }
  }
  
}


