#pragma once
#include <iostream>

template<typename T>
class Queue {
	private:
		// static constexpr int MAX_SIZE = 8;
		unsigned maxSize = 8;
		T* queue = new T[maxSize];
		unsigned length = 0;
        unsigned frontIndex = 0;

	public:
		// dont need constructor if size and frontIndex are initialized above
        // Queue() : size(0), frontIndex(0) {}

		~Queue() {
			delete[] queue;
			queue = nullptr;
		}

        bool is_empty() const { return length == 0; }
		unsigned getLength() const { return length; }

        T& front() {
            if (is_empty()) { throw std::runtime_error("Called front on empty queue"); }
            return queue[frontIndex];
        }

        const T& front() const {
            if (is_empty()) { throw std::runtime_error("Called front on empty queue"); }
            return queue[frontIndex];
        }

		void resize() {
			maxSize *= 2;
			T* resizedQueue = new T[maxSize];
			for (unsigned i = 0; i < length; ++i) {
				resizedQueue[i] = queue[(frontIndex + i) % maxSize];
			}
			queue = resizedQueue;
			delete[] resizedQueue;
			// dont need to set to nullptr because resizedQueue pointer goes out of scope
			// resizedQueue = nullptr;
			frontIndex = 0;
		}

        void push(const T& value) {
			if (length == maxSize) { resize(); }
			queue[(frontIndex + length) % maxSize] = value;
			length++;
        }

        void pop() {
            if (is_empty()) { throw std::underflow_error("Called pop on an empty queue"); }
			--length;
			frontIndex = (frontIndex + 1) % maxSize;
        }
};