#pragma once

#include "BST.h"

template <typename T>
class AVL : public BST<T> {
    private:
        enum ChildDirection {LEFT, RIGHT};

    public:
        AVL() : BST<T>() {}

        void insert(const T& key) {
            BST<T>::insert(key);

            throw std::runtime_error("finish AVL insert");
        }

        int balanceFactor(Node<T>*) const;
        void printBalanceFactors() const;

    private:
        void printBalanceFactors(Node<T>*) const;
        void updateHeight(Node<T>*);
        void setChild(Node<T>*, const ChildDirection&, Node<T>*);
        void replaceChild(Node<T>*, Node<T>*, Node<T>*);
        void rotate(Node<T>*);
        void rotateLeft(Node<T>*);
        void rotateRight(Node<T>*);
};

template <typename T>
int AVL<T>::balanceFactor(Node<T>* node) const {
    int leftHeight = (node->left != nullptr) ? node->left->height : -1;
    int rightHeight = (node->right != nullptr) ? node->right->height : -1;
    return leftHeight - rightHeight;
}

template <typename T>
void AVL<T>::printBalanceFactors() const {
    if (BST<T>::root == nullptr) {
        throw std::runtime_error("called printBalanceFactors() on an empty tree");
    }
    printBalanceFactors(BST<T>::root);
    std::cout << std::endl;
}

template <typename T>
void AVL<T>::printBalanceFactors(Node<T>* node) const {
    if (node == nullptr) { return; }

    printBalanceFactors(node->left);
    std::cout << node->key << "(" << balanceFactor(node) << "), ";
    printBalanceFactors(node->right);
}

template <typename T>
void AVL<T>::updateHeight(Node<T>* node) {
    int leftHeight = (node->left != nullptr) ? node->left->height : -1;
    int rightHeight = (node->right != nullptr) ? node->right->height : -1;
    node->height = 1 + std::max(leftHeight, rightHeight);
}

template <typename T>
void AVL<T>::setChild(Node<T>* parent, const ChildDirection& direction, Node<T>* child) {
    if (direction == LEFT) {
        parent->left = child;
    }
    else {
        parent->right = child;
    }
    if (child != nullptr) {
        child->parent = parent;
    }
    updateHeight(parent);
}

template <typename T>
void AVL<T>::replaceChild(Node<T>* parent, Node<T>* currChild, Node<T>* newChild) {
    if (parent->left == currChild) {
        setChild(parent, LEFT, newChild);
    }
    else if (parent->right == currChild) {
        setChild(parent, RIGHT, newChild);
    }
}

template <typename T>
void AVL<T>::rotate(Node<T>* node) {
    updateHeight(node);
    int balanceFactorOfNode = balanceFactor(node);

    if (balanceFactorOfNode == -2) {
        if (balanceFactor(node->right) == 1) {
            rotateRight(node->right);
        }
        rotateLeft(node);
    }
    else if (balanceFactorOfNode == 2) {
        if (balanceFactor(node->left) == -1) {
            rotateLeft(node->left);
        }
        rotateRight(node);
    }
}

template <typename T>
void AVL<T>::rotateLeft(Node<T>* node) {
    Node<T>* rightLeftChild = node->right->left;
    if (node->parent != nullptr) {
        replaceChild(node->parent, node, node->right);
    }
    else {
        BST<T>::root = node->right;
        BST<T>::root->parent = nullptr;
    }
    setChild(node->right, LEFT, node);
    setChild(node, RIGHT, rightLeftChild);
}

template <typename T>
void AVL<T>::rotateRight(Node<T>* node) {
    Node<T>* leftRightChild = node->left->right;
    if (node->parent != nullptr) {
        replaceChild(node->parent, node, node->left);
    }
    else {
        BST<T>::root = node->left;
        BST<T>::root->parent = nullptr;
    }
    setChild(node->left, RIGHT, node);
    setChild(node, LEFT, leftRightChild);
}