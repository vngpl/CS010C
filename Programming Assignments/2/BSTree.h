#pragma once

#include "Node.h"

class BSTree {
  Node* root;

public:
  BSTree() : root(nullptr) {}
  ~BSTree() { delete root; }
  BSTree(const BSTree&) = delete;
  BSTree& operator=(const BSTree&) = delete;

  void insert(const string&);
  bool search(const string&) const;
  string largest() const;
  string smallest() const;
  int height(const string&) const;
  void remove(const string&);

  void preOrder() const;
  void postOrder() const;
  void inOrder() const;

private:
  // recursive helper functions
  void insert(Node*&, const string&);
  bool search(Node*, const string&) const;
  string largest(Node*) const;
  string smallest(Node*) const;
  int height_of(Node*) const;
  void remove(Node*, Node*, const string&);

  void preOrder(Node*) const;
  void postOrder(Node*) const;
  void inOrder(Node*) const;
};
