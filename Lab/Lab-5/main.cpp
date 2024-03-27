#include <iostream>
#include "Heap.h"

using namespace std;

int menu() {
	int choice = 0;
	cout << endl << "Enter menu choice: ";
	cout << endl;
	cout << "1. Enqueue" << endl
		 << "2. Print" << endl
		 << "3. Dequeue" << endl
		 << "4. Quit" << endl;
	cin >> choice;
	// validates input
	if (!cin) { throw runtime_error("couldn't read menu choice"); }

	cin.clear();
	cin.ignore(256, '\n');
	return choice;
}

int main(){
    Heap max_heap;

    int choice = menu();

    while (choice != 4) {
		if (choice == 1) {
			int priority, jobNumber, numPages;
			cout << "Enter print job to enqueue (priority, job Number, number of pages): ";
			cin >> priority;
			// invalid input or priority < 1 throws error
			if (!cin || priority < 1) { throw runtime_error("couldn't read job priority (must be >1)"); }
			cin >> jobNumber;
			// validates input
			if (!cin) { throw runtime_error("couldn't read job number (must be an integer)"); }
			cin >> numPages;
			// invalid input or pages < 0 throws error
			if (!cin || numPages < 1) { throw runtime_error("couldnt read page amount (must be >1)"); }
			cout << endl;

			max_heap.enqueue(new PrintJob(priority, jobNumber, numPages));
		} 
		else if (choice == 2) {
			max_heap.print();
		}
		else if (choice == 3) {
			max_heap.dequeue();
		}
		//fix buffer just in case non-numeric choice entered
		choice = menu();
    }
    return 0;
}