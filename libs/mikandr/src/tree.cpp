#include "tree.h"
#include <functional>

namespace mikandr::tree {

template <typename T, typename U>
void transform(const std::shared_ptr<INode>& node, const std::function<U(T)> func) {
  if(!node) return;

  func(node);

  for(auto& child: node->m_children) {
    transform<T, U>(child, func);
  }
}

}
