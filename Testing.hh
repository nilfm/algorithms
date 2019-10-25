#ifndef __TESTING__
#define __TESTING__

#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>

namespace Testing {
    void introduce(const std::string& name, int num_tests);
    void percentage(int i, int num_tests);
    void success();
    void initialize_random(int seed = 0);
    int random_int(int minimum, int maximum);
    char random_char();
    std::string random_string(int length);
}

#endif
