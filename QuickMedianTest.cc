#include "QuickMedian.hh"
#include <iostream>
#include <cassert>

int main() {
    std::vector<int> v = {1, 1, 1, 1, 2, 3, 4, 5, 6, 7, 8};
    QuickMedian<int> m(v);
    // Median is now 3
    assert(m.median() == 3);
    m.insert(9);
    // Median is still 3
    assert(m.median() == 3);
    m.erase(1);
    // Median is now 4
    assert(m.median() == 4);
    m.erase(2);
    // Median is still 4
    assert(m.median() == 4);
    m.erase(3);
    // Median is now 5
    assert(m.median() == 5);
    m.erase(4);
    // Median is still 5
    assert(m.median() == 5);
    
    std::cout << "Passed all tests" << std::endl;
}
