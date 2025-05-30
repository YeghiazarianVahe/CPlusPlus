#pragma once

#include <vector>
#include <stdexcept>

template<typename T>
class Stack{
	std::vector<T> data;

	public:
		void push(const T& elem) { data.push_back(elem); };

		void pop() {
			if(data.empty()){
				throw std::underflow_error("Stack is empty");
			}
			data.pop_back();
		}

		T& top() {
        if (data.empty()) throw std::underflow_error("Stack is empty");
        return data.back();
    }

    bool empty() const noexcept { return data.empty(); }
    size_t size()  const noexcept { return data.size();  }
};
