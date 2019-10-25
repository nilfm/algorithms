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

void Testing::initialize_random(int seed) {
    srand(seed);
}

int Testing::random_int(int minimum, int maximum) {
    return rand()%(maximum-minimum+1) + minimum;
}

char Testing::random_char() {
        const char charset[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[rand()%max_index];
}

std::string Testing::random_string(int length) {
    std::string str(length,0);
    std::generate_n(str.begin(), length, random_char);
    return str;
}
