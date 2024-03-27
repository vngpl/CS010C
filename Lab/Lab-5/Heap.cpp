#include "Heap.h"

Heap::Heap() : numItems(0) {}

Heap::~Heap() { 
    // iterates through each array element and deallocates print jobs from memory
    for (int i = 0; i < numItems; ++i) {
        delete arr[i];
        arr[i] = nullptr;
    }
}

void Heap::enqueue(PrintJob* job) {
    if (numItems == MAX_HEAP_SIZE) { throw overflow_error("enqueuing on a full heap (can not exceed MAX_HEAP_SIZE)"); }
    // queues new job at the end of the list, post-incrementing numItems 
    arr[numItems++] = job;
    // trickles the last job up to appropriate location
    trickleUp(numItems - 1);
}


void Heap::dequeue() {
    if (numItems == 0) { throw underflow_error("dequeuing on an empty heap"); }
    // swaps highest priority job (arr[0]) with the last element (numItems-1) and decrements numItems
    swap(arr[0], arr[numItems - 1]);
    delete arr[numItems - 1];
    arr[numItems - 1] = nullptr;
    --numItems;
    // trickles new root (at index 0) down
    trickleDown(0);
}

PrintJob* Heap::highest() {
    if (numItems == 0) { throw runtime_error("called highest on an empty heap"); }
    // first element of array will have highest priority
    return arr[0];
}

void Heap::print() {
    if (numItems == 0) { throw runtime_error("called print on an empty queue"); }
    cout << "Priority: " << arr[0]->getPriority() 
         << ", Job Number: " << arr[0]->getJobNumber() 
         << ", Number of Pages: " << arr[0]->getPages() << endl;
}

// trickles down element into appropriate array index
void Heap::trickleDown(int index) {
    // calculates left and right child, sets maxIndex to current index
    int leftChildIndex = 2 * index + 1;
    int rightChildIndex = 2 * index + 2;
    int maxIndex = index;

    // if priority of left child is greater than the current max, new max is left child
    if (leftChildIndex < numItems && arr[leftChildIndex]->getPriority() > arr[maxIndex]->getPriority()) {
        maxIndex = leftChildIndex;
    }
    // if priority of right child is greater than the current max, new max is right child
    if (rightChildIndex < numItems && arr[rightChildIndex]->getPriority() > arr[maxIndex]->getPriority()) {
        maxIndex = rightChildIndex;
    }

    if (maxIndex != index) {
        // swaps the current index with the max left or right child
        swap(arr[index], arr[maxIndex]);
        // recursively checks for an index greater than max index to trickle down
        trickleDown(maxIndex);
    }
}

void Heap::trickleUp(int index) {
    // base case, once index 0 is reached, terminate recursive calls
    if (index <= 0) { return; }
    int parentIndex = (index - 1) / 2;
    // if the child's priority is greater than its parent's priority, swap
    // trickle the parent index up until 0 is reached
    if (arr[index]->getPriority() > arr[parentIndex]->getPriority()) {
        swap(arr[index], arr[parentIndex]);
        trickleUp(parentIndex);
    }
}