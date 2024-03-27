#include "Node.h"

// Node::Node() : left(nullptr), middle(nullptr), right(nullptr), parent(nullptr) {}
Node::Node(const string& key) : small(key), left(nullptr), middle(nullptr), right(nullptr), parent(nullptr) {}

// node is full when large is not empty
bool Node::isFull() const { return !(large.empty()); }
// if left, middle, and right pointers are null, node is a leaf
bool Node::isLeaf() const { return (left == nullptr && middle == nullptr && right == nullptr); }