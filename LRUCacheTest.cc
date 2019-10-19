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
		std::cout << std::boolalpha << cache.get(x) << std::endl;
	}
	std::cout << std::endl;

	//Now the 6 should be the last one
	std::cout << "Adding 7" << std::endl;
	cache.put(7, 14);
	std::cout << "Getting 6" << std::endl;
	std::cout << cache.get(6) << std::endl;
	std::cout << "Getting 7" << std::endl;
	std::cout << cache.get(7) << std::endl;
}
