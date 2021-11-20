//============================================================================
// Name        : AVLTree
// Author      : Bonnie Bell
// Version     :
// Copyright   : Your copyright notice
// Description : AVL Tree functions
//============================================================================

#include "AVLTree.h"

#include <iostream>

using namespace std;
//************** already implemented helper functions
AVLTree::AVLTree(int t_data, AVLTree* t_parent, AVLTree* t_left, AVLTree* t_right) {
    data = t_data;
    height = 0;
    parent = t_parent;
    left = t_left;
    right = t_right;
}

bool AVLTree::isLeaf() {
    //insert code here
    return ((left == nullptr) and (right == nullptr));
}

uint32_t AVLTree::getHeight() {
    uint32_t leftHeight = -1;
    uint32_t rightHeight = -1;

    if (left != nullptr){
        leftHeight = left->getHeight();
    }
    if (right != nullptr){
        rightHeight = right->getHeight();
    }
    return max(leftHeight, rightHeight) + 1;
}

//******************************************************

int AVLTree::getBalance() {
    int leftHeight = -1;
    int rightHeight = -1;
    if (left != nullptr){
        leftHeight = left->getHeight();
    }
    if (right != nullptr){
        rightHeight = right->getHeight();
    }

    return leftHeight - rightHeight;
}

AVLTree* AVLTree::rotateRight() {
    AVLTree* x = left;
    AVLTree* T2 = x->right;

    // rotate
    x->right = this;
    x->parent = this->parent;
    parent = x;
    left = T2;
    T2->parent = this;

    return x;
}

AVLTree* AVLTree::rotateLeft() {
    AVLTree* y = right;
    AVLTree* T2 = y->left;

    // rotate
    y->left = this;
    y->parent = this->parent;
    parent = y;
    right = T2;
    T2->parent = this;

    return y;
}

AVLTree* AVLTree::rebalance() {
    bool isBal = isBalanced();
    if (isLeaf()){
        return this;
    }
    if (parent != nullptr){
        if (isBal){
            parent->rebalance();
        }
        else {
            int bal = getBalance();
            if (bal > 1 && data > left->data){
                return rotateRight();
            }
            if (bal < -1 && data < right->data){
                return rotateLeft();
            }
            if (bal > 1 && data > left->data){
                left = left->rotateLeft();
                return rotateRight();
            }
            if (bal < -1 && data < right->data){
                right = right->rotateRight();
                return rotateLeft();
            }

        }    
    }
    if (parent == nullptr && !isBal){
        int bal = getBalance();
        if (bal > 1 && data > left->data){
            return rotateRight();
        }
        if (bal < -1 && data < right->data){
            return rotateLeft();
        }
        if (bal > 1 && data > left->data){
            left = left->rotateLeft();
            return rotateRight();
        }
        if (bal < -1 && data < right->data){
            right = right->rotateRight();
            return rotateLeft();
        }


    }
    // return this; whiich should be the root
    return this;
}

AVLTree* AVLTree::insert(int new_data) {
    AVLTree* root = this;

    if (new_data < root->data){
        if (left == nullptr){
            root->left = new AVLTree(new_data, root);
            return root;
        }
        left->parent = root;
        left->insert(new_data);
    }
    if (new_data >= root->data){
        if (right == nullptr){
            root->right = new AVLTree(new_data, root);
            return root;
        }
        right->parent = root;
        right->insert(new_data);
    }

    root = root->rebalance();

    return root;
}


//***************************
//Do not edit code below here
uint32_t AVLTree::countNodes() {
    //insert code here
    if (isLeaf()) {
        return 1;
    }
    if (left != nullptr) {
        if (right != nullptr) {
            return 1 + left->countNodes() + right->countNodes();
        }
        return 1+ left->countNodes();
    }
    return 1 + right->countNodes();

}

void AVLTree::updateHeight() {
    //insert code here
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
    if ( isLeaf() ) {
        return true;
    }
    if (left == nullptr) {
        return ( right->getHeight() < 1 );
    }
    if (right == nullptr) {
        return ( left->getHeight() < 1 );
    }
    return ( left->isBalanced() and right->isBalanced() and abs(getBalance() < 2) );
}
