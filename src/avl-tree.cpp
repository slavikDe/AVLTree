#pragma once
#include "avl-tree.hpp"

AvlTree::AvlTree(){

};

void AvlTree::SetValue(Key key, Value value) {
  std::shared_ptr<Node> node = FindNode(key);
  if (node.get() == nullptr) {
    AddNode(key, value);
  } else {
    node->value = value;
  }
};

Value AvlTree::FindValue(Key key){

};

bool AvlTree::IsBalanced() {
  int min, max;
  GetSubTreeLength(root_node, min, max);

  return max - min <= 1;
};



void AvlTree::SwapWithParent(std::shared_ptr<Node> node) {
  std::shared_ptr<Node> left_child = 
};

void AvlTree::LeftRotation(std::shared_ptr<Node> node) {
  
};
void AvlTree::RigthRotation(std::shared_ptr<Node> node) {
  
};
  

void AvlTree::AddNode(Key key, Value value){
  
};

void AvlTree::Balance(){

};

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
};
