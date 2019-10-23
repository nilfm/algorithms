#include "Testing.hh"

void Testing::introduce(const std::string& name, int num_tests) {
    std::cout << "Testing " << name << ": " << num_tests << " tests" << std::endl;
}

void Testing::percentage(int i, int num_tests) {
    if (i%(num_tests/100) == 0) std::cout << "\r" << i/(num_tests/100)+1 << "%" << std::flush;
}

void Testing::success() {
    std::cout << std::endl << "Passed all tests" << std::endl;    
}

