#ifndef MIKANDR_TREE_H
#define MIKANDR_TREE_H

#include <cstddef>
#include <optional>
#include <vector>
#include <functional>

namespace mikandr::tree {

class INode {
protected:
  std::vector<std::shared_ptr<INode>> m_children;
  std::weak_ptr<INode> m_parent;

  template <typename T, typename U>
  friend void transform(const std::shared_ptr<INode>& node, const std::function<U(T)> func);

public:
  virtual ~INode() = default;
  void set_parent(std::shared_ptr<INode> parent) {
    m_parent = parent;
  }
  size_t size() { return m_children.size(); }
  std::shared_ptr<INode>& operator[](std::size_t i) { return m_children.at(i); }
  const std::shared_ptr<INode>& operator[](std::size_t i) const { return m_children.at(i); }
  void add_child(std::shared_ptr<INode> child) {
    m_children.push_back(child);
  }


};

}


#endif
