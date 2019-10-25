#include "CircularQueue.hh"
#include "Testing.hh"
#include <iostream>
#include <queue>
#include <cassert>

template<class T>
class CircularQueueTest {
private:
    std::queue<T> q; 
    int max_size;
public:
    // Creates a circular queue with space for max_size elements
    CircularQueueTest(int _max_size) {
        max_size = _max_size;
    };
    ~CircularQueueTest() {};
    
    // Returns true if the queue is empty
    bool empty() {
        return q.size() == 0;
    }
    
    // Returns true if the queue is full
    bool full() {
        return size() == max_size;
    }
    
    // Returns the number of elements in the queue
    int size() {
        return q.size();
    }
    
    // Inserts element x into the queue. If the queue is full, returns false and does nothing.
    bool push(T& x) {
        if (full()) return false;
        q.push(x);
        return true;
    }
    
    // Removes the oldest element in the queue. If the queue is empty, returns false and does nothing.
    bool pop() {
        if (empty()) return false;
        q.pop();
        return true;
    }
    
    // Returns the oldest element in the queue. If the queue is empty, returns T().
    T front() {
        if (empty()) return T();
        return q.front();
    }
    
    // Returns the newest element in the queue. If the queue is empty, returns T().
    T back() {
        if (empty()) return T();
        return q.back();
    }
};

int main() {
    Testing::initialize_random();
    int NUM_TESTS = 10000000;
    Testing::introduce("Circular Queue", NUM_TESTS);
    CircularQueue<int> cq(10000);
    CircularQueueTest<int> test(10000);
    for (int i = 0; i < NUM_TESTS; i++) {
        Testing::percentage(i, NUM_TESTS);
        int ins = Testing::random_int(0, 999);
        cq.push(ins);
        test.push(ins);
        if (not cq.empty() and Testing::random_int(0, 2) == 0) {
            cq.pop();
            test.pop();
        }
        assert(cq.front() == test.front());
        assert(cq.back() == test.back());
    }
    Testing::success();
}
