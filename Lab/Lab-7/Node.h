#pragma once

#include <string>
using namespace std;

class Node {
	private:
		string key;
		int height;
		Node *left;
		Node *right;
		Node *parent;
		
		Node(const string&);

	public:
		friend class AVLTree;
};

