#include <iostream>
#include "AVLTree.h"

using namespace std;

int menu() {
	int choice = 0;
	cout << endl << "Enter menu choice: ";
	cout << endl;
	cout 
		<< "1. Insert" << endl
		<< "2. Print" << endl
		<< "3. Quit" << endl;
	cin >> choice;
	// verifies that input is a valid integer
	if (!cin) {
		throw runtime_error("error reading choice : must be an integer value (1 - 3)");
	}
	// verifies that values are between 1 and 5
	else if (choice < 1 || choice > 5) {
		throw runtime_error("invalid range : value must be between 1 and 3");
	}

	// fix buffer just in case non-numeric choice entered
	// also gets rid of newline character
	cin.clear();
	cin.ignore(256, '\n');
	return choice;
}

int main( ) {

	AVLTree tree;

	int choice = menu();

	string entry;

	while (choice != 3) {
		if (choice == 1) {
			cout << "Enter string to insert: ";
			getline(cin, entry);
			if (entry.empty()) { 
				throw runtime_error("error reading input : string may not be empty");
			}
			cout << endl;

			tree.insert(entry);
		} 
		else if (choice == 2) {
			tree.printBalanceFactors();
		} 
		//fix buffer just in case non-numeric choice entered
		choice = menu();
	}

	return 0;
}