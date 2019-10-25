#include "../MaxMinStack.hh"
#include "../Testing.hh"
#include <iostream>
#include <string>
#include <vector>
#include <cassert>

template<class T>
class MaxMinStackTest {
private:
    std::vector<T> v;
public:
    MaxMinStackTest() {}

    // Inserts x at the top of the stack
    void push(const T& x) {
        v.push_back(x);
    }
    
    // Removes the top-most element in the stack. If the stack is empty, return false and does nothing
    bool pop() {
        if (empty()) return false;
        v.pop_back();
        return true;
    }
    
    // Returns the top-most element in the stack, or T() if empty
    T top() {
        if (empty()) return T();
        return v[v.size()-1];
    }

    // Returns the smallest element in the stack, or T() if empty
    T min() {
        if (empty()) return T();
        T best = v[0];
        for (T x : v) if (x < best) best = x;
        return best;
    }
    
    // Returns the greatest element in the stack, or T() if empty
    T max() {
        if (empty()) return T();
        T best = v[0];
        for (T x : v) if (x > best) best = x;
        return best;
    }
    
    // Returns true if the stack is empty or false otherwise
    bool empty() {
        return size() == 0;
    }
    
    // Returns the number of elements in the stack
    int size() {
        return v.size();
    }
};


int main() {
    Testing::initialize_random();
    MaxMinStack<int> st;
    MaxMinStackTest<int> test;
    int NUM_TESTS = 50000;
    Testing::introduce("MaxMinStack", NUM_TESTS);
    for (int i = 0; i < NUM_TESTS; i++) {
        Testing::percentage(i, NUM_TESTS);
        int ins = Testing::random_int(0, 999);
        st.push(ins);
        test.push(ins);
        if (not st.empty() and Testing::random_int(0, 2) == 0) {
            st.pop();
            test.pop();
        }
        assert(st.top() == test.top());
        assert(st.min() == test.min());
        assert(st.max() == test.max());
    }
    Testing::success();
}
