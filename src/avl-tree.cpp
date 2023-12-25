#include "avl-tree.hpp"
#include <iostream>

AvlTree::AvlTree() {}

void AvlTree::SetValue(Key key, Value value) {
  node_ptr_t node = FindNode(key);

  if (node.get() == nullptr) {
    AddNode(key, value);
  } else {
    node->value = value;
  }
}

Value AvlTree::FindValue(Key key) {
  auto node = FindNode(key);

  if (node.get() == nullptr) {
    return Value();
  }

  return node->value;
}

void AvlTree::DeleteValue(Key key) {
  auto node = FindNode(key);

  if (node.get() == nullptr) {
    return;
  }
}

bool AvlTree::IsBalanced() {
  int min, max;
  GetSubTreeLength(root_node, min, max);

  return max - min <= 1;
}

bool AvlTree::IsBalanced(int &min, int &max) {
  GetSubTreeLength(root_node, min, max);

  return max - min <= 1;
}

bool AvlTree::IsValidTree() {
  if (root_node.get() == nullptr) {
    return true;
  }

  bool valid;

  valid = IsValidSubtree(root_node, root_node->left_node);
  if (!valid) {
    return false;
  }

  valid = IsValidSubtree(root_node, root_node->right_node);
  if (!valid) {
    return false;
  }

  return true;
}

void AvlTree::Dump(std::ostream &output) {
  output << "graph {" << std::endl;

  if (root_node.get()) {
    DumpNode(root_node, output);
  }

  output << "}" << std::endl;
}

std::shared_ptr<AvlTree::Node> AvlTree::FindNode(Key key) {
  auto current = root_node;

  while (current.get() != nullptr) {
    if (current->key == key) {
      break;
    }

    if (current->key > key) {
      current = current->left_node;
    } else {
      current = current->right_node;
    }
  }

  return current;
}

void AvlTree::AddNode(Key key, Value value) {
  node_ptr_t new_node = std::make_shared<Node>();

  new_node->value = value;
  new_node->key = key;

  if (root_node.get() == nullptr) {
    root_node = new_node;
    return;
  }

  auto parent_node = FindParentNodeForNewKey(key);
  new_node->parent_node = parent_node;

  if (key < parent_node->key) {
    parent_node->left_node = new_node;
  } else {
    parent_node->right_node = new_node;
  }

  node_ptr_t unbalanced_child_node = FindUnbalancedGrandParentUp(new_node);
  if (unbalanced_child_node.get() == nullptr) {
    return;
  }

  BalanceNode(unbalanced_child_node);
}

std::shared_ptr<AvlTree::Node> AvlTree::FindParentNodeForNewKey(Key key) {
  auto current = root_node;

  while (true) {
    node_ptr_t next;

    if (current->key > key) {
      next = current->left_node;
    } else if (current->key < key) {
      next = current->right_node;
    }

    if (next.get() == nullptr) {
      break;
    }

    current = next;
  }

  return current;
}

std::shared_ptr<AvlTree::Node>
AvlTree::FindUnbalancedGrandParentUp(node_ptr_t node) {
  if (node == root_node) {
    return nullptr;
  }

  while (node->parent_node != root_node) {
    node_ptr_t parent = node->parent_node;

    if (!IsSubtreeBalanced(parent->parent_node)) {
      return node;
    }

    node = parent;
  }

  return nullptr;
}

void AvlTree::BalanceNode(node_ptr_t child_node) {
  bool is_left_subtree = IsLeftChild(child_node);
  bool is_left_element = IsLeftChild(child_node->parent_node);

  std::cout << (is_left_element ? "L" : "R") << (is_left_subtree ? "L" : "R")
            << std::endl;

  if (!is_left_element && !is_left_subtree) {
    RRRotation(child_node->parent_node->parent_node);
  } else if (is_left_element && is_left_subtree) {
    LLRotation(child_node->parent_node->parent_node);
  } else if (is_left_element && !is_left_subtree) {
    LRRotation(child_node->parent_node->parent_node);
  } else {
    RLRotation(child_node->parent_node->parent_node);
  }
}

bool AvlTree::IsLeftChild(node_ptr_t child_node) {
  return child_node == child_node->parent_node->left_node;
}

bool AvlTree::IsSubtreeBalanced(node_ptr_t root) {
  int min, max;
  GetSubTreeLength(root, min, max);

  return max - min <= 1;
}

void AvlTree::GetSubTreeLength(node_ptr_t node, int &min, int &max) {
  if (node.get() == nullptr) {
    min = -1;
    max = -1;
    return;
  }

  int left_min, left_max, rigth_min, rigth_max;

  GetSubTreeLength(node->left_node, left_min, left_max);
  GetSubTreeLength(node->right_node, rigth_min, rigth_max);

  min = left_min < rigth_min ? left_min : rigth_min;
  max = left_max > rigth_max ? left_max : rigth_max;

  min++;
  max++;
}

bool AvlTree::IsValidSubtree(node_ptr_t parent, node_ptr_t child) {
  if (child.get() == nullptr) {
    return true;
  }

  if (child->parent_node != parent) {
    return false;
  }

  bool valid;

  valid = IsValidSubtree(child, child->left_node);
  if (!valid) {
    return false;
  }

  valid = IsValidSubtree(child, child->right_node);
  if (!valid) {
    return false;
  }

  return true;
}

void AvlTree::DumpNode(node_ptr_t node, std::ostream &output) {
  static int point_i = 0;

  output << node->key << " -- ";
  if (node->left_node.get()) {
    output << node->left_node->key << " [side=L]" << std::endl;

    DumpNode(node->left_node, output);
  } else {
    output << "p" << point_i << std::endl;
    output << "p" << point_i << " [shape=point]" << std::endl;
    point_i++;
  }

  output << node->key << " -- ";
  if (node->right_node.get()) {
    output << node->right_node->key << " [side=R]" << std::endl;

    DumpNode(node->right_node, output);
  } else {
    output << "p" << point_i << std::endl;
    output << "p" << point_i << " [shape=point]" << std::endl;
    point_i++;
  }
}

void AvlTree::RRRotation(node_ptr_t root) {
  auto r = root->right_node;
  SwapWithParent(r);

  std::swap(r->left_node, r->right_node);
  std::swap(root->left_node, root->right_node);

  SwapNodes(root, false, r, true);
}

void AvlTree::LLRotation(node_ptr_t root) {
  auto l = root->left_node;
  SwapWithParent(l);

  std::swap(l->left_node, l->right_node);

  std::swap(root->left_node, root->right_node);

  SwapNodes(root, true, l, false);
}

void AvlTree::LRRotation(node_ptr_t root) {
  auto l = root->left_node;
  auto r = l->right_node;

  RRRotation(l);

  LLRotation(root);
}

void AvlTree::RLRotation(node_ptr_t root) {
  auto r = root->right_node;
  auto l = r->left_node;

  LLRotation(r);

  RRRotation(root);
}

void AvlTree::SwapWithParent(node_ptr_t node) {
  auto parent = node->parent_node;

  std::swap(node->key, parent->key);
  std::swap(node->value, parent->value);
}

void AvlTree::SwapNodes(node_ptr_t node1_parent, bool is_left1,
                        node_ptr_t node2_parent, bool is_left2) {
  node_ptr_t node1 =
      is_left1 ? node1_parent->left_node : node1_parent->right_node;
  node_ptr_t node2 =
      is_left2 ? node2_parent->left_node : node2_parent->right_node;

  if (node1 == node2) {
    std::cout << "swap same" << std::endl;
  }

  bool node1_exists = node1.get() != nullptr;
  bool node2_exists = node2.get() != nullptr;

  if (!node1_exists && !node2_exists) {
    std::cout << "discard" << std::endl;
    return;
  } else if (!node1_exists) {
    std::cout << "move" << std::endl;
    MoveNode(node2, node1_parent, is_left1);
    return;
  } else if (!node2_exists) {
    std::cout << "move" << std::endl;
    MoveNode(node1, node2_parent, is_left2);
    return;
  }

  std::cout << "swap" << std::endl;

  node_ptr_t &link_in_parent1 =
      is_left1 ? node1_parent->left_node : node1_parent->right_node;

  node_ptr_t &link_in_parent2 =
      is_left2 ? node2_parent->left_node : node2_parent->right_node;

  std::swap(link_in_parent1, link_in_parent2);

  std::swap(node1->parent_node, node2->parent_node);
}

void AvlTree::MoveNode(node_ptr_t from, node_ptr_t to_parent, bool is_to_left) {
  node_ptr_t &link_in_to_parent =
      is_to_left ? to_parent->left_node : to_parent->right_node;

  link_in_to_parent = from;

  if (from->parent_node.get()) {
    node_ptr_t &link_in_from_parent = IsLeftChild(from)
                                          ? from->parent_node->left_node
                                          : from->parent_node->right_node;
    link_in_from_parent = nullptr;
  }

  from->parent_node = to_parent;
}
