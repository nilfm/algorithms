#ifndef __MAXMIN_STACK__
#define __MAXMIN_STACK__

#include <stack>

// T has to offer a default constructor T() and a comparison operator <
template<class T>
class MaxMinStack {
private:
    std::stack<T> st;
    std::stack<T> mins;
    std::stack<T> maxs; 

public:
    MaxMinStack() {}
    MaxMinStack(std::stack<T> other) {
        std::stack<T> rev;
        while (not other.empty()) {
            rev.push(other.top());
            other.pop();
        }
        while (not rev.empty()) {
            push(rev.top());
            rev.pop();
        }
    }

    // Inserts x at the top of the stack
    void push(const T& x) {
        if (empty()) {
            st.push(x);
            mins.push(x);
            maxs.push(x);
        }
        else {
            st.push(x);
            mins.push(std::min(x, mins.top()));
            maxs.push(std::max(x, maxs.top())); 
        }
    }
    
    // Removes the top-most element in the stack. If the stack is empty, return false and does nothing
    bool pop() {
        if (empty()) return false;
        st.pop();
        mins.pop();
        maxs.pop();
        return true;
    }
    
    // Returns the top-most element in the stack, or T() if empty
    T top() {
        if (empty()) return T();
        return st.top();
    }

    // Returns the smallest element in the stack, or T() if empty
    T min() {
        if (empty()) return T();
        return mins.top();
    }
    
    // Returns the greatest element in the stack, or T() if empty
    T max() {
        if (empty()) return T();
        return maxs.top();
    }
    
    // Returns true if the stack is empty or false otherwise
    bool empty() {
        return size() == 0;
    }
    
    // Returns the number of elements in the stack
    int size() {
        return st.size();
    }
};

#endif
