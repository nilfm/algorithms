#include "MaxMinStack.hh"
#include <iostream>
#include <string>
#include <vector>

int main() {
	MaxMinStack<int> st;
	std::cout << "Trying to pop from empty stack: " << std::boolalpha << st.pop() << std::endl << std::endl;
	std::vector<int> test = {1, 3, 2, 4, 5, 0, -1, 6};
	for (int x : test) {
		st.push(x);
		std::cout << "Pushing " << x << std::endl;
		std::cout << "Top: " << st.top() << std::endl;
		std::cout << "Min: " << st.min() << std::endl;
		std::cout << "Max: " << st.max() << std::endl << std::endl;
	}
	while (not st.empty()) {
		std::cout << "Popping " << st.top() << std::endl;
		st.pop();
		if (not st.empty()) {
			std::cout << "Top: " << st.top() << std::endl;
			std::cout << "Min: " << st.min() << std::endl;
			std::cout << "Max: " << st.max() << std::endl;
		}
		else std::cout << "Empty" << std::endl;
		std::cout << std::endl;
	}
	
	std::cout << "Constructing from std::stack with 1, 2, 3, 4:" << std::endl;
	std::stack<int> other;
	for (int x : {1, 2, 3, 4}) other.push(x);
	MaxMinStack<int> st2(other);
	while (not st2.empty()) {
		std::cout << "Popping " << st2.top() << std::endl;
		st2.pop();
		if (not st2.empty()) {
			std::cout << "Top: " << st2.top() << std::endl;
			std::cout << "Min: " << st2.min() << std::endl;
			std::cout << "Max: " << st2.max() << std::endl;
		}
		else std::cout << "Empty" << std::endl;
		std::cout << std::endl;
	}
}
