#include "QuickMedian.hh"
#include "QuickMedianVec.hh"
#include <cstdlib>
#include <iostream>
#include <cassert>

int main() {
    srand(0);
    QuickMedian<int> q;
    QuickMedianVec<int> v;
    for (int i = 0; i < 10000; i++) {
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
    
    std::cout << "Passed all tests" << std::endl;
}
