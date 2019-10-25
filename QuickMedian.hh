#ifndef __QUICK_MEDIAN__
#define __QUICK_MEDIAN__

#include <set>
#include <vector>
#include <cmath>

// T has to implement the comparison operator <
template<class T>
class QuickMedian {
private:
    std::multiset<T> low, high;
    T small_high() {
        return *(high.begin());
    }
    T big_low() {
        return *(--low.end());
    }
    void rebalance() {
        if (std::abs((int)low.size()-(int)high.size()) < 2) return;
        if (low.size() + 1 < high.size()) {
            T to_move = small_high();
            high.erase(high.begin());
            low.insert(to_move);
        }
        else {
            T to_move = big_low();
            low.erase(--low.end());
            high.insert(to_move);
        }
    }
public:
    QuickMedian() {}
    QuickMedian(const std::vector<T>& v) {
        for (const T& x : v) insert(x);
    }
    ~QuickMedian() {}
    
    // Inserts x into the structure
    void insert(const T& x) {
        if (low.size() == 0 or x > big_low()) high.insert(x);
        else low.insert(x);
        
        rebalance();
    }
    
    // Erases one occurrence of x from the structure. If it's not there, returns false and does nothing
    bool erase(const T& x) {
        auto it = low.find(x);
        if (it != low.end()) low.erase(it);
        else {
            auto it2 = high.find(x);
            if (it == high.end()) return false;
            high.erase(it2);
        }
        rebalance();
        return true;
    }
    
    // Returns the median of the elements currently in the structure. If the structure is empty, returns T()
    T median() {
        if (empty()) return T();
        if (low.size() == high.size()) return big_low();
        else if (low.size() == high.size()+1) return big_low();
        else return small_high();
    }
    
    // Returns true if there are no elements in the structure
    bool empty() {
        return size() == 0;
    }
    
    // Returns the number of elements currently in the structure
    int size() {
        return low.size() + high.size();
    }
};

#endif
