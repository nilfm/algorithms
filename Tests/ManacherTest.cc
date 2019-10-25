// Manacher's algorithm: Longest palindromic substring in O(n) time.

#include "../StringAlgorithms.hh"
#include "../Testing.hh"
#include <string>
#include <cassert>
#include <iostream>

bool is_palindrome(const std::string& s) {
    int i = 0, j = s.size()-1;
    while (i < j) {
        if (s[i] != s[j]) return false;
        i++, j--;
    }
    return true;
}

std::string ManacherTest(const std::string& s) {
    int n = s.size();
    int best_size = 0;
    std::string best = "";
    for (int i = 0; i < n; i++) {
        for (int j = n-1; j >= i and j-i+1 > best_size; j--) {
            std::string current = s.substr(i, j-i+1);
            if (is_palindrome(current)) {
                best_size = j-i+1;
                best = current;
            }
        }
    }
    return best;
}

int main() {
    Testing::initialize_random();
    int NUM_TESTS = 100000;
    Testing::introduce("Manacher", NUM_TESTS);
    for (int i = 0; i < NUM_TESTS; i++) {
        Testing::percentage(i, NUM_TESTS);
        std::string text = Testing::random_string(Testing::random_int(1, 30));
        assert(StringAlgorithms::manacher(text) == ManacherTest(text));
    }
    Testing::success();
}
