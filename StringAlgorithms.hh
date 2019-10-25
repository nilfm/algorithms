#ifndef __STRING_ALGORITHMS__
#define __STRING_ALGORITHMS__

#include <string>
#include <vector>

namespace StringAlgorithms {
    std::vector<int> compute_kmp(const std::string& pattern) {
        int n = pattern.size();
        std::vector<int> res(n);
        int i = 1, j = 0;
        res[0] = 0;
        while (i < n) {
            if (pattern[i] == pattern[j]) {
                res[i] = res[i-1] + 1;
                i++;
                j++;
            }
            else {
                while (pattern[i] != pattern[j] and j > 0) {
                    j = res[j-1];
                }
                if (pattern[i] == pattern[j]) {
                    res[i] = res[j] + 1;
                }
                else res[i] = 0;
                i++;
            }
        }
        return res;
    }

    int kmp(const std::string& text, const std::string& pattern) {
        std::vector<int> v = compute_kmp(pattern);
        int m = text.size();
        int n = pattern.size();
        int i = 0, j = 0;
        while (i < m) {
            if (text[i] == pattern[j]) {
                i++;
                j++;
            }
            else {
                if (j != 0) j = v[j-1];
                else i++;
            }
            if (j == n) return i-n;
        }
        return -1;
    }
}

#endif
