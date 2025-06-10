#ifndef MIKANDR_TREE_H
#define MIKANDR_TREE_H

#include <optional>
#include <vector>

namespace mikandr {

template<typename T>
class treenode {
  std::optional<T> m_parent;
  std::vector<std::optional<T>> m_children;

public:

};

}

#endif
