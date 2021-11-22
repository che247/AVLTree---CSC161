//============================================================================
// Name        : AVLTree
// Author      : Bonnie Bell
// Version     :
// Copyright   : Your copyright notice
// Description : AVL Tree functions
//============================================================================
#include "AVLTree.h"

#include <iostream>

int COUNT = 10;

using namespace std;
//************** already implemented helper functions
AVLTree::AVLTree(int t_data, AVLTree *t_parent, AVLTree *t_left,
                 AVLTree *t_right) {
  data = t_data;
  height = 0;
  parent = t_parent;
  left = t_left;
  right = t_right;
}

bool AVLTree::isLeaf() {
  // insert code here
  return ((left == nullptr) and (right == nullptr));
}

uint32_t AVLTree::getHeight() { return height; }

//******************************************************

int AVLTree::getBalance() {
  int leftHeight = -1;
  int rightHeight = -1;
  if (left != nullptr) {
    leftHeight = left->getHeight();
  }
  if (right != nullptr) {
    rightHeight = right->getHeight();
  }

  return leftHeight - rightHeight;
}

AVLTree *AVLTree::rotateRight() {
  AVLTree *x = left;

  if (x->right != nullptr) {
    left = x->right;
    (x->right)->parent = this;
  } else {
    AVLTree *T2 = x->right;
    left = T2;
  }

  x->right = this;
  x->parent = parent;
  x->updateHeight();
  parent = x;

  updateHeight();

  return x;
}

AVLTree *AVLTree::rotateLeft() {
  AVLTree *y = right;

  if (y->left != nullptr) {
    right = y->left;
    (y->left)->parent = this;
  } else {
    AVLTree *T2 = y->left;
    right = T2;
  }

  y->left = this;
  y->parent = parent;
  y->updateHeight();
  parent = y;

  updateHeight();

  return y;
}

AVLTree *AVLTree::rebalance() {
  bool isBal = isBalanced();
  int bal = getBalance();

  if (isLeaf()) {
    return this;
  }

  if (isBal) {
    return this;
  } else {
    if (bal > 1 && (left->left != nullptr)) {
      return rotateRight();
    }
    if (bal < -1 && (right->right) != nullptr) {
      return rotateLeft();
    }
    if (bal > 1 && (left->right) != nullptr) {
      left = left->rotateLeft();
      return rotateRight();
    }
    if (bal < -1 && (right->left) != nullptr) {
      right = right->rotateRight();
      return rotateLeft();
    }
  }

  return this;
}

AVLTree *AVLTree::insert(int new_data) {
  AVLTree *root = this;

  if (new_data < root->data) {
    if (left == nullptr) {
      root->left = new AVLTree(new_data, root);
      (root->left)->updateHeight();
    } else {
      left->parent = root;
      left = left->insert(new_data);
    }
  }

  else if (new_data >= root->data) {
    if (right == nullptr) {
      root->right = new AVLTree(new_data, root);
      (root->right)->updateHeight();
    } else {
      right->parent = root;
      right = right->insert(new_data);
    }
  }

  root = rebalance();
  updateHeight();

  return root;
}

void AVLTree::print2D(AVLTree *root) { print2DUtil(root, 0); }

void AVLTree::print2DUtil(AVLTree *root, int space) {
  // Base case
  if (root == nullptr)
    return;

  // Increase distance between levels
  space += COUNT;

  // Process right child first
  print2DUtil(root->right, space);

  // Print current node after space
  // count
  cout << endl;
  for (int i = COUNT; i < space; i++)
    cout << " ";
  cout << root->data << "\n";

  // Process left child
  print2DUtil(root->left, space);
}

//***************************
// Do not edit code below here
uint32_t AVLTree::countNodes() {
  // insert code here
  if (isLeaf()) {
    return 1;
  }
  if (left != nullptr) {
    if (right != nullptr) {
      return 1 + left->countNodes() + right->countNodes();
    }
    return 1 + left->countNodes();
  }
  return 1 + right->countNodes();
}

void AVLTree::updateHeight() {
  // insert code here
  if (isLeaf()) {
    height = 0;
    return;
  }
  if (left != nullptr) {
    left->updateHeight();
    if (right != nullptr) {
      right->updateHeight();
      height = (1 + max(left->getHeight(), right->getHeight()));
      return;
    }
    height = 1 + left->getHeight();
    return;
  }
  right->updateHeight();
  height = 1 + right->getHeight();
  return;
}

bool AVLTree::isBalanced() {
  if (isLeaf()) {
    return true;
  }
  if (left == nullptr) {
    return (right->getHeight() < 1);
  }
  if (right == nullptr) {
    return (left->getHeight() < 1);
  }
  return (left->isBalanced() and right->isBalanced() and (getBalance() > -2) and
          (getBalance() < -2));
}
