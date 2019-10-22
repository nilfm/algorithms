#include "CircularQueue.hh"

int main() {
    CircularQueue<int> q(5);
    for (int i = 1; i <= 6; i++) {
        std::cout << "Pushing " << i << std::endl;
        std::cout << std::boolalpha << q.push(i) << std::endl;
        std::cout << "Queue full: " << std::boolalpha << q.full() << std::endl;
        std::cout << "Queue empty: " << std::boolalpha << q.empty() << std::endl << std::endl;
    }
    std::cout << "Size: " << q.size() << std::endl;
    std::cout << "Front element: " << q.front() << std::endl;
    std::cout << "Back element: " << q.back() << std::endl << std::endl;
    for (int i = 0; i < 6; i++) {
        std::cout << "Popping..." << std::endl;
        std::cout << std::boolalpha << q.pop() << std::endl;
std::cout << "Queue full: " << std::boolalpha << q.full() << std::endl;
        std::cout << "Queue empty: " << std::boolalpha << q.empty() << std::endl << std::endl;
    }
}
