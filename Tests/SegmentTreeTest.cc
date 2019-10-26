#include "../SegmentTree.hh"
#include "../Testing.hh"
#include <vector>
#include <cassert>

int gcd(int a, int b) {
    if (a < b) std::swap(a, b);
    if (b == 0) return a;
    return gcd(b, a%b);
}

class GCD {
public:
    int operator()(int a, int b) {
        return gcd(a, b);
    }    
};

class SegmentTreeTest {
private:
    std::vector<int> v;
    
public:
    // Constructs a Fenwick Tree of size max_size with all zeroes
    SegmentTreeTest(int max_size) {
        v = std::vector<int>(max_size, 0);
    }    
    
    // Constructs a Fenwick Tree of size v.size() with the elements of v
    SegmentTreeTest(const std::vector<int>& _v) {
        v = _v;
    }    
    
    // Returns the sum of the interval [i, j]
    int query(int i, int j) {
        int total = 0;
        for (int k = i; k <= j; k++) {
            total = gcd(total, v[k]);
        }
        return total;
    }
    
    // Adds the value k to the i'th element
    void update(int i, int k) {
        v[i] = k;
    }
};

int main() {
    Testing::initialize_random();
    int NUM_TESTS = 100000;
    Testing::introduce("Segment Tree", NUM_TESTS);
    SegmentTree<int, GCD> s(1000);
    SegmentTreeTest t(1000);
    for (int i = 0; i < NUM_TESTS; i++) {
        Testing::percentage(i, NUM_TESTS);
        int upd = Testing::random_int(0, 10);
        int pos = Testing::random_int(0, 999);
        s.update(pos, upd);
        t.update(pos, upd);
        int last = Testing::random_int(1, 999);
        int first = Testing::random_int(0, last);
        assert(s.query(first, last) == t.query(first, last));
    } 
    Testing::success();
}
