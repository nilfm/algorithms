#include "LRUCache.hh"
#include "Testing.hh"
#include <iostream>
#include <unordered_map>
#include <cstdlib>
#include <cassert>

template<class K, class V>
class LRUCacheTest {
private:
    int max_size;
    unsigned long long current;
    std::unordered_map<K, std::pair<unsigned long long, V>> m; 
    
public:
    // Constructs an LRU Cache with space for max_size elements (K, V pairs)
    LRUCacheTest(int _max_size) {
        max_size = _max_size;
        current = 0;
    }
    ~LRUCacheTest() {}
    
    // Returns the value associated with key K. If not present, returns V()
    V get(K key) {
        if (not m.count(key)) return V();
        if (m[key].first < current) {
            m[key].first = current;
            current++;
        } 
        return m[key].second;
    }
    
    // Inserts the key-value pair into the LRU Cache. Returns true if the key wasn't there already, and false otherwise.
    bool put(K key, V value) {
        if (m.count(key)) {
            if (m[key].first < current) {
                m[key].first = current;
                current++;    
            }
            m[key].second = value;
            return false;
        }
        else {
            if (full()) {
                unsigned long long minim = current;
                for (auto& p : m) minim = std::min(minim, p.second.first);
                for (auto& p : m) {
                    if (p.second.first == minim) {
                        m.erase(p.first);
                        m.insert(std::make_pair(key, std::make_pair(current, value)));
                        current++;    
                        break;
                    }
                }
            }
            else {
                m.insert(std::make_pair(key, std::make_pair(current, value)));
                current++;
            }
            return true;
        }
    }
    
    // Returns true if the cache is full
    bool full() {
        return size() == max_size;
    }
    
    // Returns true if the cache is empty
    bool empty() {
        return size() == 0;
    }
    
    // Returns the number of key-value pairs in the cache
    int size() {
        return m.size();
    }
    
};

int main() {
    LRUCache<int, int> cache(500);
    LRUCacheTest<int, int> test(500);
    int NUM_TESTS = 1000000;
    srand(0);
    Testing::introduce("LRU Cache", NUM_TESTS);
    for (int i = 0; i < NUM_TESTS; i++) {
        Testing::percentage(i, NUM_TESTS);
        int ins = rand()%1000;
        cache.put(ins, i);
        test.put(ins, i);
        
        int check = rand()%1000;
        assert(cache.get(check) == test.get(check));
    }
    Testing::success();
}
