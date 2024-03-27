#pragma once

#include "Node.h"

class Tree {
	private:
		Node *root;

	public:
		Tree();
		~Tree();
		Tree(const Tree&) = delete;
		Tree& operator=(const Tree&) = delete;
		
		void insert(const string&);
		void preOrder() const;
		void inOrder() const;
		void postOrder() const;
		void remove(const string&);
		bool search (const string&) const;

	private:
		void destructTree(Node*);
		void insert(Node*, const string&);
		void preOrder(Node*) const;
		void inOrder(Node*) const;
		void postOrder(Node*) const;
		void remove(Node*, Node*, const string&);
		bool search(Node*, const string&) const;
		void split(Node*, const string&);
};