#include "LRUCache.hh"
#include <iostream>

int main() {
    LRUCache<int, int> cache(5);
    for (int i = 1; i <= 6; i++) {
        std::cout << "Adding " << i << std::endl;
        std::cout << std::boolalpha << cache.put(i, 2*i) << std::endl;
    }
    std::cout << std::endl;
    std::vector<int> v = {1, 2, 3, 4, 5};
    for (auto x : v) {
        std::cout << "Getting " << x << std::endl;
        std::cout << cache.get(x) << std::endl;
    }
    std::cout << std::endl;

    //Now the 6 should be the last one
    std::cout << "Adding 7" << std::endl;
    cache.put(7, 14);
    std::cout << "Getting 6" << std::endl;
    std::cout << cache.get(6) << std::endl;
    std::cout << "Getting 7" << std::endl;
    std::cout << cache.get(7) << std::endl;
    
    std::cout << std::endl << "Copy constructor:" << std::endl;
    LRUCache<int, int> cache2(cache);
    cache2.put(5, 15);
    std::cout << "Getting 5 from old cache: " << cache.get(5) << std::endl;
    std::cout << "Getting 5 from new cache: " << cache2.get(5) << std::endl;
    std::cout << "Old cache size: " << cache.size() << std::endl;
    std::cout << "New cache size: " << cache2.size() << std::endl;

    std::cout << std::endl << "Move constructor:" << std::endl;
    LRUCache<int, int> cache3(std::move(cache2));
    std::cout << "Getting 7 from old cache: " << cache2.get(7) << std::endl;
    std::cout << "Getting 7 from new cache: " << cache3.get(7) << std::endl;
    std::cout << "Old cache size: " << cache2.size() << std::endl;
    std::cout << "New cache size: " << cache3.size() << std::endl;
    
    std::cout << std::endl << "Copy assignment operator:" << std::endl;
    LRUCache<int, int> cache4(0);
    cache4 = cache;
    cache4.put(5, 20);
    std::cout << "Getting 5 from old cache: " << cache.get(5) << std::endl;
    std::cout << "Getting 5 from new cache: " << cache4.get(5) << std::endl;
    std::cout << "Old cache size: " << cache.size() << std::endl;
    std::cout << "New cache size: " << cache4.size() << std::endl;

    std::cout << std::endl << "Move assignment operator:" << std::endl;
    LRUCache<int, int> cache5(0);
    cache5 = std::move(cache3);
    std::cout << "Getting 7 from old cache: " << cache3.get(7) << std::endl;
    std::cout << "Getting 7 from new cache: " << cache5.get(7) << std::endl;
    std::cout << "Old cache size: " << cache3.size() << std::endl;
    std::cout << "New cache size: " << cache5.size() << std::endl;
}
