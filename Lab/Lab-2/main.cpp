#include <iostream>
#include "IntList.h"

using namespace std;

int main() {
  IntList list;

  cout << "empty: " << list << endl;
  list.push_front(3);
  cout << "push front 3: " << list << endl;
  list.push_back(1);
  cout << "push back 1: " << list << endl;
  list.push_back(5);
  cout << "push back 5: " << list << endl;
  list.push_front(2);
  cout << "push front 2: " << list << endl;
  list.pop_back();
  cout << "pop back: " << list << endl;
  list.pop_front();
  cout << "pop front: " << list << endl;
  
  // cout << "EMPTY?" << endl;
  // if (list.empty()) {
  //   cout << "true" << endl;
  // }
  // else {
  //   cout << "false" << endl;
  // }

  // cout << "PUSH FRONT '4'" << endl;
  // cout << "EMPTY?" << endl;
  // list.push_front(4);
  // if (list.empty()) {
  //   cout << "true" << endl;
  // }
  // else {
  //   cout << "false" << endl;
  // }

  // cout << "PRINTING LIST" << endl;
  // cout << list << endl;

  // list.push_front(11);
  // list.push_front(19);
  // list.push_front(16);
  // list.push_front(9);

  // cout << "PRINTING LIST" << endl;
  // cout << list << endl;

  // cout << "PRINTING LIST IN REVERSE" << endl;
  // list.printReverse();
  // cout << endl;

  // list.pop_front();
  // cout << list << endl;

  // list.push_back(99);
  // cout << list << endl;

  // list.pop_back();
  // list.pop_back();
  // list.pop_back();
  // list.pop_back();
  // cout << list << endl;

  // cout << "TESTING DESTRUCTOR" << endl;
  // {
  //   IntList tempList;
  //   tempList.push_front(19);
  //   tempList.push_front(9);
  //   tempList.push_front(11);
  //   tempList.push_front(16);

  //   cout << "BEFORE DESTRUCTION: " << tempList << endl;
  // }
  // cout << "AFTER DESTRUCTION" << endl;
       
  return 0;
}
