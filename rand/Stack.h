#pragma once

template<typename T>
class Stack {
	private:
		static constexpr int MAX_SIZE = 8;
		T data[MAX_SIZE];
		int size = 0;
	public:
		// dont need constructor if size and frontIndex are initialized above
		// Stack() : size(0) {}
		
        	bool is_empty() const { return size <= 0; }

        T& top() {
		if (is_empty()) { throw std::underflow_error("Called top on empty stack."); }
		return data[size - 1];
	}

	const T& top() const {
		if (is_empty()) { throw std::underflow_error("Called top on empty stack."); }
		return data[size - 1];
	}

	void push(const T& value) {
		if (size >= static_cast<int>(MAX_SIZE)) { throw std::overflow_error("Called push on full stack."); }
		data[size++] = value;
	}

	void pop() {
		if (is_empty()) { throw std::underflow_error("Called pop on empty stack."); }
		--size;
	}
};
