#include <iostream>
#include <chrono>
#include <cstdlib>
#include <stdexcept>
#include <vector>

using std::cout;
using std::endl;
 // replaced 'steady_clock' with 'system_clock' to fix error
using std::chrono::system_clock;
using std::chrono::microseconds;
using std::chrono::time_point;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;

// initializes constant number of clocks per millisecond and number range
constexpr int CLOCKS_PER_MS = CLOCKS_PER_SEC/1000;
constexpr int NUMBERS_SIZE = 50000;

// generates random numbers between 0 and 50000
int genRandInt(int low, int high) {
	return low + rand() % (high - low + 1);
}

// fills 3 arrays with randomly generated numbers
void fillArrays(int arr1[], int arr2[],int arr3[]) {
	// iterates 'NUMBERS_SIZE' times, filling with 'NUMBERS_SIZE' elements
	for(int i = 0; i < NUMBERS_SIZE; ++i) {
		arr1[i] = genRandInt(0,NUMBERS_SIZE);
		arr2[i] = arr1[i];
		arr3[i] = arr1[i];
	}
}

// partitions the array for quicksort
int QPartition(int numbers[], int low, int high) {
	int midpoint = low + (high - low) / 2;
	// sets pivot to the middle of the array
	int pivot = numbers[midpoint];

	bool done = false;

	while (!done) {
		// increments the low index until value greater than the pivot is reached
		while (numbers[low] < pivot) {
			low++;
		}
		// decrements the high index until value less than pivot is reached
		while (pivot < numbers[high]) {
			high--;
		}

		// partioning is complete if the low index is greater than or equal to the high index
		if (low >= high) { 
			done = true;
		}
		// swaps the lowest and highest index, until stopping case of low >= high is satisfied
		else {
			std::swap(numbers[low], numbers[high]);
			low++;
			high--;
		}
	}
	return high;
}

void Quicksort_midpoint(int numbers[], int i, int k) {
	// base case : if low index is greater than high, return
	if (i >= k) { return; }
	// determines new low index after partitioning
	int lowEndIndex = QPartition(numbers, i, k);
	// sorts elements from low partition
	Quicksort_midpoint(numbers, i, lowEndIndex);
	// sorts elements from high partition
	Quicksort_midpoint(numbers, lowEndIndex + 1, k);
}

void Quicksort_medianOfThree(int numbers[], int i, int k) {
	if (i >= k) { return; }

	// calculates midpoint for median of three
	int midpoint = i + (k - i) / 2;
	// performs swaps to ensure that the midpoint is between the low ('i') and high ('k')
	if (numbers[i] > numbers[midpoint]) {
		std::swap(numbers[i], numbers[midpoint]);
	}
	if (numbers[i] > numbers[k]) {
		std::swap(numbers[i], numbers[k]);
	}
	if (numbers[midpoint] < numbers[k]) {
		std::swap(numbers[midpoint], numbers[k]);
	}

	// same as quicksort midpoint
	int lowEndIndex = QPartition(numbers, i, k);
	Quicksort_medianOfThree(numbers, i, lowEndIndex);
	Quicksort_medianOfThree(numbers, lowEndIndex + 1, k);
}

void InsertionSort(int numbers[], int numbersSize) {
	// iterates over the array starting from 2nd element
	for (int i = 1; i < numbersSize; ++i) {
		int j = i;
		// compares current index with previous index to check if previous is greater
		while (j > 0 && numbers[j] < numbers[j - 1]) {
			// performs swap if previous is greater, decrementing j to continue comparison
			// with new previous index
			std::swap(numbers[j], numbers[j - 1]);
			--j;
		}
	}
}

// A helper function that will let us know if we have sorted
// everything
static bool is_sorted(int numbers[], int numbersSize) {
	if (numbersSize <= 0) return true;
	int last = numbers[0];
	for(int i=0; i < numbersSize; ++i) {
		int curr = numbers[i];
		if (curr < last) return false;
		last = curr;
	}
	return true;
}

// copies elements of vector into the array
static void copy_vector_into_array(const std::vector<int>& source, int array[]) {
	for(int i=0;i<static_cast<int>(source.size()); ++i) {
		array[i] = source[i];
	}
}

int main() {
	std::vector<int> sample;
	// preallocates a vector of 50000 elements
	sample.reserve(NUMBERS_SIZE);
	// fills vector with values from 0 to 50000
	for(int i=0; i<NUMBERS_SIZE; ++i) {
		sample.push_back(rand() % (NUMBERS_SIZE + 1));
	}
	
	// run tests across a bunch of sizes
	int test_sizes[4] = { 10, 100, 1000, 50000 };
	int test_array[NUMBERS_SIZE];
	for(int i=0; i<4; ++i) {
		int size = test_sizes[i];
		cout << endl;
		cout << "-------------------- size " << size << " --------------------" << endl;

		// QUICK SORT MIDPOINT
		{
			// copies elements of vector to the array
			copy_vector_into_array(sample, test_array);
			// begin timing before calling sort
			time_point<system_clock> start = high_resolution_clock::now();
			Quicksort_midpoint(test_array, 0, size - 1);
			// end timing after finishing sort
			time_point<system_clock> stop = high_resolution_clock::now();
			// get microseconds of time
			microseconds duration = duration_cast<microseconds>(stop - start);
			cout << duration.count() << " ms for quick sort midpoint" << endl;
			// calls 'is_sorted' to check if array is sorted after the alogrithm is finished sorting
			cout << "Sort is " << ((is_sorted(test_array,size))?"GOOD":"BAD") << endl;
		}
		
		// QUICK SORT MEDIAN
		{
			copy_vector_into_array(sample, test_array);
			time_point<system_clock> start = high_resolution_clock::now();
			Quicksort_medianOfThree(test_array, 0, size - 1);

			time_point<system_clock> stop = high_resolution_clock::now();
			microseconds duration = duration_cast<microseconds>(stop - start);
			cout << duration.count() << " ms for quick sort median" << endl;
			cout << "Sort is " << ((is_sorted(test_array,size))?"GOOD":"BAD") << endl;
		}
		
		// INSERTION SORT
		{
			copy_vector_into_array(sample, test_array);
			time_point<system_clock> start = high_resolution_clock::now();
			InsertionSort(test_array, size);

			time_point<system_clock> stop = high_resolution_clock::now();
			microseconds duration = duration_cast<microseconds>(stop - start);
			cout << duration.count() << " ms for insertion sort " << endl;
			cout << "Sort is " << ((is_sorted(test_array,size))?"GOOD":"BAD") << endl;
		}

	}	
	return 0;
}