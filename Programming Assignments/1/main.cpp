#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Node {
    string payload;
    Node* next;
};

// allocates memory for a new node, sets the payload to
// the input string parameter, and returns a pointer to the node
Node* newNode(const string& payload) {
    Node *newNode = new Node;
	newNode->payload = payload;
	newNode->next = nullptr;
	return newNode;
}

// creates the circular list of nodes by looping through
// the vector of strings
Node* loadGame(int n, const vector<string>& names) {
    Node* head = nullptr;
    Node* prev = nullptr;
    string name;

    for (int i = 0; i < n; ++i) {
        name = names.at(i);
		// when the list is empty the head and prev point to
		// the same node
        if (head == nullptr) {
            head = newNode(name);
            prev = head;
        }
		// prev is shifted forward with each new node 
		else {
            prev->next = newNode(name);
            prev = prev->next;
        }
    }
	// checks that prev points to a node and makes the last node
	// point back to the head (making the list circular)
    if (prev != nullptr) { prev->next = head; }
    return head;
}

void print(const Node* start) {
  const Node* curr = start;
  // checks for nullptr because no node in the list should point to nullptr
  // once the list reaches back to the start, breaks out of the loop
  while (curr != nullptr) {
    cout << curr->payload << endl;
    curr = curr->next;
    if (curr == start) { break; }
  }
}

// josephus w circular list, k = num skips
Node* runGame(Node* start, int k) {
    Node* curr = start;
    Node* prev = curr;
	// loop terminates once the last person is reached
    while (curr->next != curr) {
        for (int i = 0; i < k; ++i) {
			prev = curr;
			curr = curr->next;
        }

        // cout << curr->payload << endl;

        prev->next = curr->next;
        delete curr;
        curr = prev->next;
    }

    return curr;
}

int main() {
	// n = num names; k = num skips (minus 1)
    int n=1, k=1;
	string name;
    vector<string> names;

    cin >> n >> k;
    if (!cin) { throw runtime_error("error reading n and k from input"); }
    
	// EOF or . ends input
	while (cin >> name && name != ".") { names.push_back(name); }

    // initialize and run game
    Node* startPerson = loadGame(n, names);
    Node* lastPerson = runGame(startPerson, k);

    if (lastPerson != nullptr) {
        cout << lastPerson->payload << " wins!" << endl;
    } else {
        cout << "error: null game" << endl;
    }

	// deallocates memory for the lastPerson node and sets to nullptr
	delete lastPerson;
	lastPerson = nullptr;

    return 0;
}

