#pragma once
#include <stdexcept>

template<typename T>
class stack {
	private:
		static constexpr unsigned MAX_SIZE = 20;
		T data[MAX_SIZE];
		int size;
	public:
		// default constructor, initializes size to 0
		stack() : size(0) {}

		// push(T val): inserts a new element (val) of type T (T could be integer or string)
		// into the data. If the data array is full, this function should throw an overflow_error
		// exception with error message "Called push on full stack.".
		void push(const T& value) {
			if (size >= static_cast<int>(MAX_SIZE)) { throw std::overflow_error("Called push on full stack."); }
			data[size++] = value;
		}

		// empty(): returns true if the stack is empty otherwise it returns false.
		bool empty() const { return size <= 0; }

		// pop(): removes the last element from data. If the data array is empty, this function
		// should throw an outofrange exception with error message "Called pop on empty stack.".
		void pop() {
			if (empty()) { throw std::underflow_error("Called pop on empty stack."); }
			--size;
		}

		// pop_two(): removes the last two elements from data. If the data array is empty or is
		// of size 1, this function should throw an out_of_range exception. If empty then the error
		// message should be "Called pop_two on empty stack." If the size is 1 then the error
		// message should be "Called pop_two on a stack of size 1.".
		void pop_two() {
			if (empty()) { throw std::out_of_range("Called pop_two on empty stack."); }
			else if (size == 1) { throw std::out_of_range("Called pop_two on a stack of size 1."); }
			size -= 2;
		}
		// returns the first item in the stack
		T& top() { 
			if (empty()) { throw std::underflow_error("Called top on empty stack."); }
			return data[size - 1]; 
		}
		// const reference of the first item in the stack
		const T& top() const { 
			if (empty()) { throw std::underflow_error("Called top on empty stack."); }
			return data[size - 1]; 
		}
};
