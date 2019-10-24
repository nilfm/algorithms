#include "Testing.hh"

void Testing::introduce(const std::string& name, int num_tests) {
    std::cout << "Testing " << name << ": " << num_tests << " tests" << std::endl;
}

void Testing::percentage(int i, int num_tests) {
    if (i%(num_tests/100) == 0) {
        int percent = i/(num_tests/100)+1;
        std::cout << '\r';
        for (int k = 0; k < percent/4; k++) {
            std::cout << '=';
        }
        std::cout << "> " << i/(num_tests/100)+1 << '%' << std::flush;
    }
}

void Testing::success() {
    std::cout << std::endl << "Passed all tests" << std::endl;    
}

