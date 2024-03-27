#pragma once

template <typename T>
class Node {
    public:
        T key;
        Node<T>* left;
        Node<T>* right;
        Node(const T& key) : key(key), left(nullptr), right(nullptr) {}

        // Destructor is not needed as BST class is responsible
        // for managing the memory that it allocates

        // Node() : left(nullptr), right(nullptr) {}
        // ~Node();
        // Node(const Node&) = delete;
        // Node& operator=(const Node&) = delete;
};