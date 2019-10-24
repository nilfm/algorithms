#ifndef __CIRCULAR_QUEUE__
#define __CIRCULAR_QUEUE__

#include <vector>

template<class T>
class CircularQueue {
private:
    std::vector<T> q; 
    int max_size;
    int sz;
    int start, end;
public:
    // Creates a circular queue with space for max_size elements
    CircularQueue(int _max_size) {
        q = std::vector<T>(_max_size);
        max_size = _max_size;
        sz = 0;
        start = 0, end = -1;
    };
    ~CircularQueue() {};
    
    // Returns true if the queue is empty
    bool empty() {
        return sz == 0;
    }
    
    // Returns true if the queue is full
    bool full() {
        return sz == max_size;
    }
    
    // Returns the number of elements in the queue
    int size() {
        return sz;
    }
    
    // Inserts element x into the queue. If the queue is full, returns false and does nothing.
    bool push(T& x) {
        if (full()) return false;
        end = (end+1)%max_size;
        q[end] = x;
        sz++;
        return true;
    }
    
    // Removes the oldest element in the queue. If the queue is empty, returns false and does nothing.
    bool pop() {
        if (empty()) return false;
        start = (start+1)%max_size;
        sz--;
        return true;
    }
    
    // Returns the oldest element in the queue. If the queue is empty, returns T().
    T front() {
        if (empty()) return T();
        return q[start];
    }
    
    // Returns the newest element in the queue. If the queue is empty, returns T().
    T back() {
        if (empty()) return T();
        return q[end];
    }
};

#endif
