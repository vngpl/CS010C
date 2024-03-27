#pragma once

#include <iostream>
#include <stdexcept>
#include "Node.h"

template <typename T>
class BST {
    private:
        Node<T>* root;

    public:
        BST() : root(nullptr) {}

        ~BST() {
            destroy(root);
            root = nullptr;
        }

        BST(const BST&) = delete;
        BST& operator=(const Node<T>&) = delete;

        bool search(const T& key) const { return search(root, key); }

        void insert(const T& key) {
            if (search(key)) { throw std::runtime_error("inserting a duplicate"); }
            insert(root, key);
        }

        void remove(const T&);
        int height(const T&) const;

        void preOrder() const { preOrder(root); }
        void inOrder() const { inOrder(root); }
        void postOrder() const { postOrder(root); }

    private:
        void destroy(Node<T>* node) {
            if (node == nullptr) { return; }

            destroy(node->left);
            destroy(node->right);

            delete node;
        }

        bool search(Node<T>*, const T&) const;
        void insert(Node<T>*&, const T&);
        void remove(Node<T>*, const T&);
        int height(Node<T>*) const;

        void preOrder(Node<T>*) const;
        void inOrder(Node<T>*) const;
        void postOrder(Node<T>*) const;
};

template<typename T>
bool BST<T>::search(Node<T>* node, const T& key) const {
    if (node == nullptr) {
        return false;
    }

    if (node->key == key) {
        return true;
    }

    return (key < node->key) ? search(node->left, key) : search(node->right, key);
}

template<typename T>
void BST<T>::insert(Node<T>*& node, const T& key) {
    if (node == nullptr) {
        node = new Node<T>(key);
        return;
    }

    (key < node->key) ? insert(node->left, key) : insert(node->right, key);
}

template<typename T>
void BST<T>::remove(const T& key) { remove(root, key); }

template<typename T>
void BST<T>::remove(Node<T>* node, const T& key) {
    if (node == nullptr) { return; }
    throw std::runtime_error("finish remove");
}

template<typename T>
int BST<T>::height(const T& key) const {
    Node<T>* currNode = root;

    while (currNode != nullptr) {
        if (currNode->key == key) {
            return height(currNode);
        }
        else if (key < currNode->key) {
            currNode = currNode->left;
        }
        else {
            currNode = currNode->right;
        }
    }

    return -1;
}

template<typename T>
int BST<T>::height(Node<T>* node) const {
    if (node == nullptr) { return -1; }

    return std::max(height(node->left), height(node->right)) + 1;
}

template<typename T>
void BST<T>::preOrder(Node<T>* node) const {
    if (node == nullptr) { return; }

    std::cout << node->key << " ";
    preOrder(node->left);
    preOrder(node->right);
}

template<typename T>
void BST<T>::inOrder(Node<T>* node) const {
    if (node == nullptr) { return; }

    inOrder(node->left);
    std::cout << node->key << " ";
    inOrder(node->right);
}

template<typename T>
void BST<T>::postOrder(Node<T>* node) const {
    if (node == nullptr) { return; }

    postOrder(node->left);
    postOrder(node->right);
    std::cout << node->key << " ";
}

// template<typename T>
// BST<T>::BST() : root(nullptr) {}
// template<typename T>
// BST<T>::~BST() {
//     destroy(root);
//     root = nullptr;
// }
// template<typename T>
// void BST<T>::destroy(Node<T>* node) {
//     if (node == nullptr) { return; }
//     destroy(node->left);
//     destroy(node->right);
//     delete node;
// }
// template<typename T>
// bool BST<T>::search(const T& key) const { return search(root, key); }
// template<typename T>
// void BST<T>::insert(const T& key) {
//     if (search(key)) {
//         throw std::runtime_error("inserting a duplicate key");
//     }
//     insert(root, key);
// }
// template<typename T>
// void BST<T>::preOrder() const { preOrder(root); }
// template<typename T>
// void BST<T>::inOrder() const{ inOrder(root); }
// template<typename T>
// void BST<T>::postOrder() const { postOrder(root); }