#ifndef __FENWICK_TREE__
#define __FENWICK_TREE__

#include <vector>

#define LSB(i) ((i) & -(i))

// T has to implement an associative + operator
template<class T>
class FenwickTree {
private:
    std::vector<T> tree;
    int sz;
    T sum(int i) {
        i++;
        T sum = 0;
        while (i > 0) {
            sum += tree[i];
            i -= LSB(i);
        }
        return sum;
    }  
public:
    // Constructs a Fenwick Tree of size max_size with all zeroes
    FenwickTree(int max_size) {
        sz = max_size+1;
        tree = std::vector<T>(sz, 0);
    }    
    
    // Constructs a Fenwick Tree of size v.size() with the elements of v
    FenwickTree(const std::vector<T>& v) {
        sz = v.size()+1;
        tree = std::vector<T>(sz, 0);
        for (int i = 0; i < sz-1; i++) add(i, v[i]);
    }    
    
    // Returns the sum of the interval [i, j]
    T sum(int i, int j) {
        return sum(j) - sum(i-1);
    }
    
    // Adds the value k to the i'th element
    void add(int i, T k) {
        i++;
        while (i < sz) {
            tree[i] += k;
            i += LSB(i);
        }
    }};

#endif
