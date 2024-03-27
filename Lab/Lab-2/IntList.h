#pragma once

#include <iostream>

struct IntNode {
    int data;
    IntNode *prev;
    IntNode *next;
    IntNode(int data) : data(data), prev(nullptr), next(nullptr) {}
};

class IntList {
private:
  IntNode dummyHead;
  IntNode dummyTail;
public:
  IntList()
    : dummyHead(-1),
      dummyTail(-1)
  {
    dummyHead.prev = nullptr;
    dummyHead.next = &dummyTail;

    dummyTail.prev = &dummyHead;
    dummyTail.next = nullptr;
  }

  ~IntList();
  IntList(const IntList&);
  IntList& operator=(const IntList&);
  void push_front(int value);
  void pop_front();
  void push_back(int value);
  void pop_back();
  bool empty() const;
  friend std::ostream & operator<<(std::ostream &out, const IntList &rhs);
  void printReverse() const;
};
