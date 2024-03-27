#include "Tree.h"

Tree::Tree() : root(nullptr) {}
Tree::~Tree() { destructTree(root); }

// recursively deallocates nodes from tree, then deallocates final node (root)
void Tree::destructTree(Node* node) {
    if (node == nullptr) { return; }

    destructTree(node->left);
    destructTree(node->middle);
    destructTree(node->right);
    delete node;
}

void Tree::insert(const string &key) {
    // if root is empty, fill
    if (root == nullptr) {
        root = new Node(key);
        return;
    }
    // if key already exists, throw error
    else if (search(key)) { 
        throw runtime_error("inserting a duplicate"); 
    }
    else {
        insert(root, key);
    }
}
void Tree::insert(Node* node, const string& key) {
    // recursively find node until leaf case is satisfied
    if (!node->isLeaf()) {
        if (key < node->small) {
            insert(node->left, key);
        }
        else if (!node->isFull() || key < node->large) {
            insert(node->middle, key);
        }
        else {
            insert(node->right, key);
        }            
    }
    // reaches else once node is a leaf
    else {
        // if not full, insert key into node and adjust small/large as needed
        if (!node->isFull()) {
            // inserts key into large by default, if key is smaller than small, swap keys
            node->large = key;
            if (node->large < node->small) {
                swap(node->large, node->small);
            }
        }
        // node is full, split is required
        else {
            split(node, key);
        }
    }
}

// rebalance is called when inserting on a full node
void Tree::split(Node* node, const string& key) {
    if (key < node->small) {
        // if nodes parent does not exist, reached root, split
        if (node->parent == nullptr) {
            throw runtime_error("implement case where there is no parent 1");
            return;
        }
        // else parent exists
        if (!node->parent->isFull()) {
            throw runtime_error("implement case where parent is not full (rotate keys) 1");
            return;
        }
        // keep track of node's parent before recursively splitting parent when node and its parent are full
        Node* oldParent = node->parent;
        split(node->parent, node->small);
        swap(node->large, node->small);
        node->large.clear();
        oldParent->middle = new Node(key);
    }
    else if (key > node->large) {
        if (node->parent == nullptr) {
            throw runtime_error("implement case where there is no parent 2");
            return;
        }
        // key becomes right node of parent
        if (!node->parent->isFull()) {
            swap(node->parent->large, node->large);
            node->parent->right = new Node(key);
            node->parent->right->parent = node;
            return;
        }
        throw runtime_error("implement case where parent is full and there is a parent (split parent) 2");
        // split(node->parent, node->large);
    }
    else {
        // if key inserted is in the middle and node is root, key becomes new root
        if (node->parent == nullptr) {
            Node* newRoot = new Node(key);
            newRoot->left = node;
            node->parent = newRoot;
            newRoot->middle = new Node(node->large);
            newRoot->middle->parent = newRoot;
            swap(node->right, newRoot->middle->middle);
            swap(node->middle, newRoot->middle->left);
            node->large.clear();
            root = newRoot;
            return;
        }
        if (!node->parent->isFull()) {
            throw runtime_error("implement case where parent is not full (rotate keys) 3");
            return;
        }
        throw runtime_error("implement case where parent is full and there is a parent (split parent) 3");
        // split(node->parent, key);
    }
}

void Tree::preOrder() const {
    // tree must not be empty when called
    if (root == nullptr) {
        throw runtime_error("called 'preOrder' on an empty tree");
    }
    preOrder(root);
}
void Tree::preOrder(Node* node) const {
    if (node == nullptr) { return; }

    cout << node->small << ", ";
    preOrder(node->left);
    // if full, print large and visit right subtree
    if (node->isFull()) {
        cout << node->large << ", ";
        preOrder(node->middle);
        preOrder(node->right);  
    }
    // else, visit only the middle
    else {
        preOrder(node->middle); 
    }
}

void Tree::inOrder() const { 
    if (root == nullptr) {
        throw runtime_error("called 'inOrder' on an empty tree");
    }
    inOrder(root);
}
void Tree::inOrder(Node* node) const {
    if (node == nullptr) { return; }

    inOrder(node->left);
    cout << node->small << ", ";
    inOrder(node->middle);
    // if full, print large and visit right subtree
    if (node->isFull()) {
        cout << node->large << ", ";
        inOrder(node->right);
    }
}

void Tree::postOrder() const { 
    if (root == nullptr) {
        throw runtime_error("called 'postOrder' on an empty tree");
    }
    postOrder(root);
}
void Tree::postOrder(Node* node) const {
    if (node == nullptr) { return; }

    postOrder(node->left);
    postOrder(node->middle);
    cout << node->small << ", ";
    // if full, visit right subtree and print large
    if (node->isFull()) {
        postOrder(node->right);
        cout << node->large << ", ";
    }
}

void Tree::remove(const string &key) {
    // tree must not be empty when calling
    if (root == nullptr) {
        throw runtime_error("called remove on an empty tree");
    } 
    // if value isnt found in tree, throw error since nothing to remove
    else if (!search(key)) {
        throw runtime_error("key to remove was not found in tree");
    }
    else {
        remove(nullptr, root, key); 
    }
}
void Tree::remove(Node* parent, Node* node, const string& key) {
    if (node == nullptr) { return; }

    // if current node doesnt have key, keep traversing recursively
    if (!(node->small == key || node->large == key)) {
        if (key < node->small) {
            remove(node, node->left, key);
        }
        else if (!node->isFull() || key < node->large) {
            remove(node, node->middle, key);
        }
        else {
            remove(node, node->right, key);
        }
    }
    // node with key is found
    else {
        // case of leaf node (has no children)
        if (node->isLeaf()) {
            // node is root
            if (parent == nullptr) {
                // if not full, node will be empty, delete root
                if (!node->isFull()) {
                    delete node;
                    root = nullptr;
                }
                // else, remove key and adjust small/large
                else {
                    if (node->small == key) {
                        swap(node->large, node->small);
                    }
                    node->large.clear();
                }
            }
            // leaf node but not root
            else if (parent->left == node) {
                if (!node->isFull()) {
                    delete parent->left;
                    parent->left = nullptr;
                    insert(parent->middle, parent->small);
                    root = parent->middle;
                    parent->middle->parent = nullptr;
                    delete parent;
                }
                else {
                    if (node->small == key) {
                        swap(node->large, node->small);
                    }
                    node->large.clear();
                }
                // throw runtime_error("implement case where node is leaf but is not root");
            }
            else {
                if (!node->isFull()) {
                    delete parent->right;
                    parent->right = nullptr;
                    insert(parent->left, parent->small);
                    root = parent->left;
                    parent->left->parent = nullptr;
                    delete parent;
                }
                else {
                    if (node->small == key) {
                        swap(node->large, node->small);
                    }
                    node->large.clear();
                }
            }
        }
        // case of node having children
        else {
            // removing root
            if (node->parent == nullptr) {
                if (!node->isFull()) {
                    swap(node->small, node->middle->small);
                    remove(node, node->middle, key);
                }
                else {
                    throw runtime_error("implement case where parent is full");
                }
            }
            // parent is not nullptr, removing internal node
            else {
                throw runtime_error("implement case of removing internal node");
            }
        }
    }
}

bool Tree::search(const string &key) const { 
    if (root == nullptr) {
        throw runtime_error("called 'search' on an empty tree");
    }
    return search(root, key);
}
bool Tree::search(Node* node, const string& key) const {
    // continue searching as long as current node isnt nullptr
    if (node == nullptr) { 
        return false;
    }

    // if small or large contains the key, return true
    if (node->small == key || node->large == key) {
        return true;
    }
    // if less than the small, search left subtree
    if (key < node->small) {
        return search(node->left, key);
    }
    // if between small and large or large is empty, search middle subtree
    else if (!node->isFull() || key < node->large) {
        return search(node->middle, key);
    }
    // if greater than the large, search right subtree
    else {
        return search(node->right, key);
    }
}