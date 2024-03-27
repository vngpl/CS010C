#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

// creates a randomized vector containing letters of the alphabet
vector<char> createVector() {
	int vecSize = rand() % 26;
	char c = 'a';
	vector<char> vals;
	for(int i = 0; i < vecSize; i++) {
		vals.push_back(c);
		c++;
	}
	return vals;
}

template<typename T>
unsigned min_index(const vector<T>& vals, unsigned index) {
	unsigned minIndex = index;
	// loops through each index until a minimum is found
	for (unsigned i = index; i < vals.size(); ++i) {
		// compares current index to current minimum index
		if (vals.at(i) < vals.at(minIndex)) {
			minIndex = i;
		}
	}
  	return minIndex;
}

template<typename T>
void selection_sort(vector<T>& vals) {
	// compares i = 0 to next index and swaps if 
	// next index contains a new minimum value
	for (unsigned i = 0; i < vals.size(); ++i) {
		unsigned minIndex = min_index(vals, i);
		if (minIndex != i) {
			swap(vals.at(i), vals.at(minIndex));
		}
	}
}

template<typename T>
T getElement(const vector<T>& vals, int index) {
	// if (index < 0 || static_cast<unsigned>(index) > vals.size() - 1) {
	// 	throw out_of_range("index is out of bounds");
	// }
	// .at() function, throws out of range exception
	// that is caught in main()
 	return vals.at(index);
}

int main() {
	// Seeding the random number generator so we get a different
	// run every time.
	srand(time(0));

	// Fill in a vector of some random size with some random
	// characters
	vector<char> vals = createVector();
	int numOfRuns = 10;
	while(--numOfRuns >= 0) {
		cout << "Enter a number: " << endl;
		int index;
		if (not (cin >> index)) { throw runtime_error("could not read the index"); }

		// tries to get the element at given index, if element is not found
		// throws an out of range exception from getElement() function
		try {
			char curChar = getElement(vals, index);
			cout << "Element located at " << index << ": is " << curChar << endl;
		}
		// catches and outputs the exception
		catch (const out_of_range& excpt) {
			// cout << excpt.what() << endl;
			cout << "out of range exception occured" << endl;
		}
	}

	int vectorSize = 20;
	vector<int> testVector;
	cout << "BEFORE SORTING: ";
	// populates vector with 20 random integers from range 0 to 25
	for (unsigned i = 0; i < vectorSize; ++i) {
		testVector.push_back(rand() % 25);
		cout << testVector.at(i) << " ";
	}
	cout << endl;

	cout << "AFTER SORTING: ";
	selection_sort(testVector);
	for (unsigned i = 0; i < testVector.size() - 1; ++i) {
		// if the vector is out of order, sorting failed and breaks
		// out of the loop
		if (testVector.at(i) > testVector.at(i + 1)) {
			cout << "SORTING FAILED" << endl;
			break;
		}
		cout << testVector.at(i) << " ";
	}
	cout << endl;

	return 0;
}
