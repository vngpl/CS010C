#include "IntList.h"

#include <iostream>
#include <exception>

using namespace std;

ostream & operator<<(ostream &out, const IntList &rhs) {
  for (const IntNode *currNode = rhs.dummyHead.next; currNode != &rhs.dummyTail; currNode = currNode->next) {
    out << currNode->data;
    // only enters a space after the data if the next node is not the tail
    if (currNode->next != &rhs.dummyTail) {
      out << " ";
    }
  }
  return out;
}

IntList::~IntList() {
  // deallocates the node until the list has nodes then sets the dummytail's previous
  // back to the dummyhead
  while (!empty()) {
    IntNode *currNode = dummyHead.next;
    dummyHead.next = currNode->next;
    delete currNode;
  }
  dummyTail.prev = &dummyHead;
}

// initializes the member variables to the same values as the default constructor
IntList::IntList(const IntList& cpy) : dummyHead(-1), dummyTail(-1) {
  dummyHead.prev = nullptr;
  dummyHead.next = &dummyTail;
  dummyTail.prev = &dummyHead;
  dummyTail.next = nullptr;

  // uses push_back() to allocate memory for the node while appending it to the back of the list
  for (const IntNode *currNode = cpy.dummyHead.next; currNode != &cpy.dummyTail; currNode = currNode->next) {
    push_back(currNode->data);
  }
}

IntList& IntList::operator=(const IntList& rhs) {
  // checks if the left hand side and right hand side are different
  if (this != &rhs) {
    // clears the left hand side if not empty
    while (!empty()) { pop_back(); }
    // pushes back the data from the rhs to the implicit lhs list
    for (const IntNode *currNode = rhs.dummyHead.next; currNode != &rhs.dummyTail; currNode = currNode->next) {
      push_back(currNode->data);
    }
  }
  
  return *this;
}

void IntList::push_front(int value) {
  // allocates memory for the node with the user specified value
  IntNode *newNode = new IntNode(value);
  // handles case where list is empty to modify the tail
  if (empty()) {
    newNode->prev = &dummyHead;
    newNode->next = &dummyTail;
    dummyHead.next = dummyTail.prev = newNode;
  }
  else {
    newNode->prev = &dummyHead;
    newNode->next = dummyHead.next;
    dummyHead.next = dummyHead.next->prev = newNode;
  }
}

void IntList::pop_front() {
  // does nothing if list is empty, otherwise removes and deallocates the node after
  // the dummyhead
  if (empty()) { return; }
  IntNode *currNode = dummyHead.next;
  dummyHead.next = currNode->next;
  currNode->next->prev = &dummyHead;
  delete currNode;
}

void IntList::push_back(int value) {
  // if the list is empty, performs a push front
  if (empty()) { push_front(value); }
  // else deallocates the node before and adjusts the tail
  else {
    IntNode *newNode = new IntNode(value);
    newNode->prev = dummyTail.prev;
    newNode->next = &dummyTail;
    dummyTail.prev = dummyTail.prev->next = newNode;
  }
}

void IntList::pop_back() {
  // does nothing if empty
  if (empty()) { return; }
  // handles the case where theres only one node by checking if dummyhead's next and dummytail's
  // previous point to the same node
  if (dummyHead.next == dummyHead.prev) {
    delete dummyHead.next;
    dummyHead.next = &dummyTail;
    dummyTail.prev = &dummyHead;
  }
  // deallocates the last node and sets the second to last node to point to dummytail
  else {
    IntNode *newLastNode = dummyTail.prev->prev;
    newLastNode->next = &dummyTail;
    delete dummyTail.prev;
    dummyTail.prev = newLastNode;
  }
}

// if dummyhead's next is not dummytail, returns false, else returns true
bool IntList::empty() const { return dummyHead.next == &dummyTail; }

void IntList::printReverse() const {
  // starts from the end of the list and moves backwards to print the node's data
  for (const IntNode *currNode = dummyTail.prev; currNode != &dummyHead; currNode = currNode->prev) {
    cout << currNode->data << " ";
  }
}

