#include "QuickMedian.hh"
#include "Testing.hh"
#include <cstdlib>
#include <cassert>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <iostream>


// This is an auxiliary class implementing the naive way to dynamically compute medians
// It is only useful to help debug/compare outputs with the QuickMedian class

// T has to implement the comparison operator < and division by an int
template<class T>
class QuickMedianTest {
private:
    std::vector<T> v;
public:
    QuickMedianTest() {}
    QuickMedianTest(const std::vector<T>& _v) {
        v = _v;
        std::sort(v.begin(), v.end());
    }
    ~QuickMedianTest() {}
    
    // Inserts x into the structure
    void insert(const T& x) {
        v.push_back(x);
        std::sort(v.begin(), v.end());
    }
    
    // Erases one occurrence of x from the structure. If it's not there, returns false and does nothing
    bool erase(const T& x) {
        auto it = std::find(v.begin(), v.end(), x);
        if (it == v.end()) return false;
        v.erase(it);
        std::sort(v.begin(), v.end());
        return true;
    }
    
    // Returns the median of the elements currently in the structure. If the structure is empty, returns T()
    T median() {
        if (empty()) return T();
        return v[(v.size()-1)/2];
    }
    
    // Returns a random element of the structure
    T random() {
        return v[rand()%size()];
    }
    
    void print() {
        for (T x : v) std::cout << x << " ";
        std::cout << std::endl;
    }
    
    // Returns true if there are no elements in the structure
    bool empty() {
        return size() == 0;
    }
    
    // Returns the number of elements currently in the structure
    int size() {
        return v.size();
    }
};


int main() {
    int NUM_TESTS = 20000;
    srand(0);
    QuickMedian<int> q;
    QuickMedianTest<int> v;
    Testing::introduce("QuickMedian", NUM_TESTS);
    for (int i = 0; i < NUM_TESTS; i++) {
        Testing::percentage(i, NUM_TESTS);
        int ins = rand()%1000;
        q.insert(ins);
        v.insert(ins);
        if (rand()%10 == 0) {
            int del = v.random();
            q.erase(del);
            v.erase(del);
        }
        assert(q.median() == v.median());
    }
    Testing::success();
}
