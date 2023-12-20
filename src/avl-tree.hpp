#pragma once
#include <memory>

struct Value {
  int val;
};

typedef int Key;

class AvlTree {
private:
  struct Node {
    Value value;
    Key key;

    std::shared_ptr<Node> parent_node;

    std::shared_ptr<Node> left_node;
    std::shared_ptr<Node> right_node;
  };

public:
  AvlTree();

  void SetValue(Key key, Value value);

  Value FindValue(Key key);

  bool IsBalanced();

private:
  std::shared_ptr<Node> FindNode(Key key);
  void AddNode(Key key, Value value);

  void Balance();
  void GetSubTreeLength(std::shared_ptr<Node> node, int& min, int& max);

  void LeftRotation(std::shared_ptr<Node> node);
  void RigthRotation(std::shared_ptr<Node> node);
  void SwapWithParent(std::shared_ptr<Node> node);
private:
  std::shared_ptr<Node> root_node;
};
