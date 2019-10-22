#ifndef __FENWICK_TREE__
#define __FENWICK_TREE__

#include <vector>

#define LSB(i) ((i) & -(i))

class FenwickTree {
private:
    std::vector<int> tree;
    int sz;
    int sum(int i);
public:
    // Constructs a Fenwick Tree of size max_size with all zeroes
    FenwickTree(int max_size);
    
    // Constructs a Fenwick Tree of size v.size() with the elements of v
    FenwickTree(const std::vector<int>& v);
    
    // Returns the sum of the interval [i, j]
    int sum(int i, int j);
    
    // Adds the value k to the i'th element
    void add(int i, int k);
};

#endif
