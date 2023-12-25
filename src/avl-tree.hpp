#pragma once
#include <iostream>
#include <memory>

struct Value {
  int val;
};

typedef int Key;

class AvlTree {
private:
  struct Node;

  using node_ptr_t = std::shared_ptr<Node>;

  struct Node {
    Value value;
    Key key;

    node_ptr_t parent_node;

    node_ptr_t left_node;
    node_ptr_t right_node;
  };

public:
  AvlTree();

  void SetValue(Key key, Value value);

  Value FindValue(Key key);

  void DeleteValue(Key key);

  bool IsBalanced();
  // bool IsBalanced(int &min, int &max);

  bool IsValidTree();

  void Dump(std::ostream &output);

private:
  node_ptr_t FindNode(Key key);
  void AddNode(Key key, Value value);
  void DeleteNode(Key key);

  node_ptr_t FindNodeToSwap(Node root, Key key);
  

  node_ptr_t FindParentNodeForNewKey(Key key);

  node_ptr_t FindUnbalancedGrandParentUp(node_ptr_t node);

  void BalanceNode(node_ptr_t child_node);

  bool IsLeftChild(node_ptr_t child_node);

  bool IsSubtreeBalanced(node_ptr_t root);
  void GetSubTreeLength(node_ptr_t node, int &min, int &max);

  bool IsValidSubtree(node_ptr_t parent, node_ptr_t child);
  bool IsLeaf(node_ptr_t node);

  void DumpNode(node_ptr_t node, std::ostream &output);

  void RRRotation(node_ptr_t root);
  void LLRotation(node_ptr_t root);

  void LRRotation(node_ptr_t root);
  void RLRotation(node_ptr_t root);

  void SwapWithParent(node_ptr_t node);
  void SwapNodes(node_ptr_t node1_parent, bool is_left1,
                 node_ptr_t node2_parent, bool is_left2);
  void MoveNode(node_ptr_t from, node_ptr_t to_parent, bool is_to_left);

private:
  node_ptr_t root_node;
};
