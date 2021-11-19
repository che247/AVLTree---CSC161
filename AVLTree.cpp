
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
	return height;
}

//******************************************************

int AVLTree::getBalance() {
    int lHeight = -1;
    int rHeight = -1;

    if (left != nullptr){
        lHeight = left->getHeight();
    }
    if (right != nullptr){
        rHeight = right->getHeight();
    }
    
    //cout << "Balance Factor: " << lHeight - rHeight << endl;
    return (lHeight - rHeight);
}

AVLTree* AVLTree::rotateRight() {
    AVLTree* x = left;
    AVLTree* T2 = left->right;

    // rotate
    x->right = this; // address of whatever pointer is being pointed too at the moment
    left = T2;

    return x;
}

AVLTree* AVLTree::rotateLeft() {
    AVLTree* y = right;
    AVLTree* T2 = y->left;

    //rotate
    y->left = this; 
    right = T2;
    
    return  y;
}

AVLTree* AVLTree::rebalance() {
    if (isLeaf()){
        return this;
    }
    if (left != nullptr){
        left->left->rebalance();
    }
    if (right != nullptr){
        right->right->rebalance();
    }
}

AVLTree* AVLTree::insert(int new_data) {
    AVLTree* root = this;
    if (data > new_data){
        if (left == nullptr){
            // store previous node as the parent node
            left = new AVLTree(new_data, this);
        } else {
            (left)->insert(new_data);
        }
    } else {
        if (right == nullptr){
            right = new AVLTree(new_data, this);
        } else {
            (right)->insert(new_data);
        }
    }

    root->updateHeight();

    bool bal = isBalanced();
    if (bal == false){
        rebalance();
        updateHeight();
    }

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
