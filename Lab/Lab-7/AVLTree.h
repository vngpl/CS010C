#pragma once

#include "Node.h"
#include <iostream>
#include <stdexcept>

class AVLTree {
    Node* root;

    public:
        AVLTree();
        ~AVLTree();
        AVLTree(const string&) = delete;
        AVLTree& operator=(const AVLTree&) = delete;
        
        void insert(const string&);
        int balanceFactor(Node*) const;
        void printBalanceFactors() const;

    private:
        void destructTree(Node*);
        void printBalanceFactors(Node*) const;
        bool search(Node*, const string&) const;
        void updateHeight(Node*);
        void setChild(Node*, const string&, Node*);
        void replaceChild(Node*, Node*, Node*);
        void rotate(Node*);
        void rotateLeft(Node*);
        void rotateRight(Node*);
};