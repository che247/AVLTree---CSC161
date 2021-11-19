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

    cout << leftHeight - rightHeight << endl;
    return leftHeight - rightHeight;
}

AVLTree* AVLTree::rotateRight() {
    AVLTree* x = left;
    AVLTree* T2 = x->right;

    // rotate
    x->right = this;
    left = T2;

    return x;
}

AVLTree* AVLTree::rotateLeft() {
    AVLTree* y = right;
    AVLTree* T2 = y->right;

    // rotate
    y->left = this;
    right = T2;

    return y;
}

AVLTree* AVLTree::rebalance() {
    int bal = getBalance();
    if (bal > 1 && data < left->data){
        return rotateRight();
    }
    if (bal < -1 && data > right->data){
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
    // return if no balancing is required
    return this;
}

AVLTree* AVLTree::insert(int new_data) {
    AVLTree* r = this;
    if(data > new_data){
        if (left == nullptr){
            left = new AVLTree(new_data);
        }
        else {
            left->insert(new_data);
        }
    }
    else {
        if (right == nullptr){
            right = new AVLTree(new_data);
        }
        else {
            right->insert(new_data);
        }
    }
    
    updateHeight();
    cout << "New Height: " << getHeight() << endl;
    //balance if not balanced
    bool bal = isBalanced();
    if (!bal){
        rebalance();
        cout << "\n---REBALANCE---" << endl;
    }

    //cout << "You've made it to the end of insert function!" << endl;
    return r;
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
