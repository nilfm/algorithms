#ifndef __QUICK_MEDIAN_VEC__
#define __QUICK_MEDIAN_VEC__

#include <set>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <iostream>


// This is an auxiliary class implementing the naive way to dynamically compute medians
// It is only useful to help debug/compare outputs with the QuickMedian class

// T has to implement the comparison operator < and division by an int
template<class T>
class QuickMedianVec {
private:
    std::vector<T> v;
public:
    QuickMedianVec() {}
    QuickMedianVec(const std::vector<T>& _v) {
        v = _v;
        std::sort(v.begin(), v.end());
    }
    ~QuickMedianVec() {}
    
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

#endif
