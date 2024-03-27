#pragma once

#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

class Node {
	public:
		friend class Tree;

	private:
		string small;
		string large;

		Node *left;
		Node *middle;
		Node *right;
		Node *parent;

		// Add additional functions/variables here. Remember, you may not add any
		// Node * or string variables.

		// Node();
		Node(const string&);
		
		bool isFull() const;
		bool isLeaf() const;
};
