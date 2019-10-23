#include "FenwickTree.hh"
#include "Testing.hh"
#include <vector>
#include <iostream>
#include <cassert>
#include <cstdlib>

template<class T>
class FenwickTreeTest {
private:
    std::vector<T> v;

public:
    // Constructs a Fenwick Tree of size max_size with all zeroes
    FenwickTreeTest(int max_size) {
        v = std::vector<T>(max_size, 0);
    }    
    
    // Constructs a Fenwick Tree of size v.size() with the elements of v
    FenwickTreeTest(const std::vector<T>& _v) {
        v = _v;
    }    
    
    // Returns the sum of the interval [i, j]
    T sum(int i, int j) {
        T res = 0;
        for (int k = i; k <= j; k++) res += v[k];
        return res;
    }
    
    // Adds the value k to the i'th element
    void add(int i, T k) {
        v[i] += k;
    }
};

int main() {
    srand(0);
    int NUM_TESTS = 1000000;
    Testing::introduce("Fenwick Tree", NUM_TESTS);
    FenwickTree<int> f(10000);
    FenwickTreeTest<int> t(10000);
    for (int i = 0; i < NUM_TESTS; i++) {
        Testing::percentage(i, NUM_TESTS);
        int inc = rand()%1000;
        int pos = rand()%10000;
        f.add(pos, inc);
        t.add(pos, inc);
        int last = rand()%9999 + 1;
        int first = rand()%last;
        assert(f.sum(first, last) == t.sum(first, last));
    } 
    Testing::success();
}
