#pragma once
#include "avl-tree.hpp"

AvlTree::AvlTree() {}

void AvlTree::SetValue(Key key, Value value) {
  std::shared_ptr<Node> node = FindNode(key);
  if (node.get() == nullptr) {
    AddNode(key, value);
  } else {
    node->value = value;
  }
}

Value AvlTree::FindValue(Key key) {}

bool AvlTree::IsBalanced() {
  int min, max;
  GetSubTreeLength(root_node, min, max);

  return max - min <= 1;
}

void AvlTree::SwapWithParent(std::shared_ptr<Node> node) {
  auto parent = node->parent_node;

  std::swap(node->key, parent->key);
  std::swap(node->value, parent->value);
}

void AvlTree::LeftRotation(std::shared_ptr<Node> root) {}
void AvlTree::RigthRotation(std::shared_ptr<Node> root) {
  auto l = root->left_node;
  SwapWithParent(l);

  std::swap(root->left_node, root->right_node);

  std::swap(l->left_node, root->left_node);
  std::swap(l->left_node->parent_node, root->left_node->parent_node);

  std::swap(l->left_node, l->right_node);
}

void AvlTree::AddNode(Key key, Value value) {
  std::shared_ptr<Node> new_node = std::make_shared<Node>();

  auto current = root_node;
  bool is_left_subtree;
  
  new_node->key = key;
  new_node->value = value;

  while (true) {
	std::shared_ptr<Node> next;

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


}

void AvlTree::Balance() {}

void AvlTree::GetSubTreeLength(std::shared_ptr<Node> node, int &min, int &max) {
  if (node.get() == nullptr) {
    min = -1;
    max = -1;
  }

  int left_min, left_max, rigth_min, rigth_max;

  GetSubTreeLength(node->left_node, left_min, left_max);
  GetSubTreeLength(node->right_node, rigth_min, rigth_max);

  min = left_min < rigth_min ? left_min : rigth_min;
  max = left_max > rigth_max ? left_max : rigth_max;

  min++;
  max++;
}
