#include "Node.h"

Node::Node(const string& key) : key(key), height(0), left(nullptr), right(nullptr), parent(nullptr) {}