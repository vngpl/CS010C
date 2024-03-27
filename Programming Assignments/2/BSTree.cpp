#include "BSTree.h"

#include <iostream>
#include <stdexcept>

using namespace std;


void BSTree::insert(const string& key) { insert(root, key); }
void BSTree::insert(Node*& node, const string& key) {
	if (node == nullptr) {
		node = new Node(key);
		return;
	}

	if (node->key == key) {
		node->count++;
		return;
	}
	else if (key < node->key) {
		insert(node->left, key);
	}
	else {
		insert(node->right, key);
	}
}

// inserts a new node into the tree
// void BSTree::insert(const string& key) {
// 	// if root is nullptr, inserted node becomes root
// 	if (root == nullptr) {
// 		root = new Node(key);
// 		return;
// 	}

// 	// traverses binary tree to find insertion point
// 	for (Node* curr = root; curr != nullptr;) {
// 		// if node's key already exists, increment count
// 		if (curr->key == key) {
// 			curr->count++;
// 			return;
// 		}
// 		// enter left subtree if key is less than current key
// 		else if (key < curr->key) {
// 		// if left of current is nullptr, enter the node on the left
// 			if (curr->left == nullptr) {
// 				curr->left = new Node(key);
// 				return;
// 			}
// 			// else, continue moving down left
// 			else {
// 				curr = curr->left;
// 			}
// 		}
// 		// enter right subtree if key is greater than current key
// 		else if (key > curr->key) {
// 			// enters node on the right once nullptr is reached
// 			if (curr->right == nullptr) {
// 				curr->right = new Node(key);
// 				return;
// 			}
// 			else {
// 				curr = curr->right;
// 			}
// 		}
// 	}
// }

// see below for recursive approach of search(), largest(), and smallest()
bool BSTree::search(const string& key) const { return search(root, key); }
string BSTree::largest() const { return largest(root); }
string BSTree::smallest() const { return smallest(root); }

int BSTree::height(const string& key) const {
	Node *curr = root;
	int height = -1;

	while (curr != nullptr) {
		// if key is found, use height_of to get height
		if (curr->key == key) {
			height = height_of(curr);
			break;
		}
		// continue searching left or right subtrees
		else if (key < curr->key) { curr = curr->left; }
		else { curr = curr->right; }
	}

	return height;
}

// see below for recursive approach of remove(), preOrder(), postOrder(), and inOrder()
void BSTree::remove(const string& key) { remove(nullptr, root, key); }
void BSTree::preOrder() const { preOrder(root); }
void BSTree::postOrder() const { postOrder(root); }
void BSTree::inOrder() const { inOrder(root); }

void BSTree::remove(Node* parent, Node* tree, const string& key) {
	// Edge case: The key is not found (do nothing), else key exists
	if (!search(key)) { return; }

	// Recursively find the key, making the node to remove the root of the tree
	// if key is smaller, go into left tree
	if (key < tree->key) {
		remove(tree, tree->left, key);
	}
	// else, go into right tree
	else if (key > tree->key) {
		remove(tree, tree->right, key);
	}
	else {
		// Edge case: The key count is greater than 1.  Just decrement the count
		if (tree->count > 1) {
			--tree->count;
			return;
		}
		else {
			// Edge case: leaf (no children).  Just remove from parent
			if (tree->left == nullptr && tree->right == nullptr) {
				//  ==> case 1: parent is nullptr (we are removing the last node from root)
				if (parent == nullptr) {
					delete tree;
					root = nullptr;
				}
				//  ==> case 2: curr is the left child, remove it from parent
				else if (parent->left == tree) {
					delete parent->left;
					parent->left = nullptr;
				}
				//  ==> case 3: curr is the right child, remove it from parent
				else {
					delete parent->right;
					parent->right = nullptr;
				}
			}
			// Typical case:  Find the target
			else {
				Node* successorParent = tree;
				// It is either the largest key in the left tree (if one exists)
				// or the smallest key in the right tree (since not a leaf one will exist)
				Node* successor = (tree->left != nullptr) ? tree->left : tree->right;
				// if successor is in the left tree, keep going right to find largest key
				if (successor == tree->left) {
					while (successor->right != nullptr) {
						successorParent = successor;
						successor = successor->right;
					}
				}
				// else, successor is in the right tree, keep going left to find smallest key
				else {
					while (successor->left != nullptr) {
						successorParent = successor;
						successor = successor->left;
					}
				}
				// Copy the target information into the node we found, set the target count to one
				tree->key = successor->key;
				tree->count = successor->count;
				successor->count = 1;
				// one, and recursively remove it from left or right subtree (current node is the parent)
				remove(successorParent, successor, successor->key);
			}
		}
	}
}

int BSTree::height_of(Node* tree) const {
	// if tree is nullptr, height is -1
	if (tree == nullptr) { return -1; }
	// uses std max function to get the max height between left and right
	// subtrees, adding 1 to give final height
	return max(height_of(tree->left), height_of(tree->right)) + 1;
}

// outputs all left subtrees, then all right subtrees
void BSTree::preOrder(Node* tree) const {
	if (tree == nullptr) { return; }
	cout << tree->key << "(" << tree->count << "), ";
	preOrder(tree->left);
	preOrder(tree->right);
}

// outputs nodes in ascending order
void BSTree::postOrder(Node* tree) const {
	if (tree == nullptr) { return; }
	postOrder(tree->left);
	postOrder(tree->right);
	cout << tree->key << "(" << tree->count << "), ";
}

// outputs node in order
void BSTree::inOrder(Node* tree) const {
	if (tree == nullptr) { return; }
	inOrder(tree->left);
	cout << tree->key << "(" << tree->count << "), ";
	inOrder(tree->right);
}

bool BSTree::search(Node* tree, const string& key) const {
	if (tree == nullptr) { return false; }
	// if key is found return true
	if (tree->key == key) { return true; }
	// if key is larger than the current node's key, search left subtree
	else if (key < tree->key) { return search(tree->left, key); }
	// else, search right subtree
	else { return search(tree->right, key); }
}

string BSTree::largest(Node* tree) const {
	if (tree == nullptr) { return ""; }
	// if right most position is reached, return the key
	if (tree->right == nullptr) { return tree->key; }
	// recursive step, continue moving down right
	return largest(tree->right);
}

string BSTree::smallest(Node* tree) const {
	if (tree == nullptr) { return ""; }
	// if left most position reached, return key
	if (tree->left == nullptr) { return tree->key; }
	// recursive step, continue moving down left
	return smallest(tree->left);
}