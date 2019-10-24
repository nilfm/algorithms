#include "Testing.hh"

void Testing::introduce(const std::string& name, int num_tests) {
    std::cout << "Testing " << name << ": " << num_tests << " tests" << std::endl;
}

void Testing::percentage(int i, int num_tests) {
    if (i%(1 + num_tests/100) == 0) {
        int percent = i/(1 + num_tests/100)+1;
        if (i == num_tests-1) percent = 100;
        std::cout << '\r';
        for (int k = 0; k < percent/4; k++) {
            std::cout << '=';
        }
        std::cout << "> " << percent << '%' << std::flush;
    }
}

void Testing::success() {
    std::cout << std::endl << "Passed all tests" << std::endl << std::endl;    
}

