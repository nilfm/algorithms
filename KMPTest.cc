// KMP algorithm - Find an occurrence of pattern in text in O(n) time.

#include "StringAlgorithms.hh"
#include "Testing.hh"
#include <cassert>
#include <iostream>

int KMPTest(const std::string& text, const std::string& pattern) {
    int n = text.size(), m = pattern.size();
    for (int i = 0; i < n-m+1; i++) {
        bool match = true;
        for (int j = 0; match and j < m; j++) {
            if (text[i+j] != pattern[j]) match = false;
        }
        if (match) return i;
    }
    return -1;
}

int main() {
    Testing::initialize_random();
    int NUM_TESTS = 100000;
    Testing::introduce("KMP", NUM_TESTS);
    for (int i = 0; i < NUM_TESTS; i++) {
        Testing::percentage(i, NUM_TESTS);
        std::string text = Testing::random_string(Testing::random_int(1, 30));
        std::string pattern = Testing::random_string(Testing::random_int(1, 10));
        assert(StringAlgorithms::kmp(text, pattern) == KMPTest(text, pattern));
    }
    Testing::success();
}
