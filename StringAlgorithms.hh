#ifndef __STRING_ALGORITHMS__
#define __STRING_ALGORITHMS__

#include <string>
#include <vector>

namespace StringAlgorithms {
    // Separator for Manacher's algorithm
    const char SEP = '|';
    
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

    int kmp(const std::string& text, const std::string& pattern, std::vector<int> computed = {}) {
        if (computed.size() == 0) computed = compute_kmp(pattern);
        int m = text.size();
        int n = pattern.size();
        int i = 0, j = 0;
        while (i < m) {
            if (text[i] == pattern[j]) {
                i++;
                j++;
            }
            else {
                if (j != 0) j = computed[j-1];
                else i++;
            }
            if (j == n) return i-n;
        }
        return -1;
    }
    
    bool contains(const std::string& text, const std::string& pattern) {
        return kmp(text, pattern) != -1;
    }
        
    std::string add_boundaries(const std::string& s) {
        int n = s.size();
        std::string res(2*n+1, ' ');
        for (int i = 0; i < n; i++) {
            res[2*i] = SEP;
            res[2*i + 1] = s[i];
        }
        res[2*n] = SEP;
        return res;
    }

    std::string remove_boundaries(const std::string& s) {
        int n = s.size();
        std::string res(n/2, ' ');
        for (int i = 0; i < n/2; i++) {
            res[i] = s[2*i+1];
        }
        return res;
    }

    std::vector<int> compute_manacher(const std::string& s) {
        int sz = s.size();
        std::vector<int> v(sz);
        int c = 0, r = 0;
        int m = 0, n = 0;
        for (int i = 1; i < sz; i++) {
            if (i > r) {
                v[i] = 0;
                m = i-1;
                n = i+1;
            }
            else {
                int ii = c*2-i;
                if (v[ii] < r-i-1) {
                    v[i] = v[ii];
                    m = -1; 
                }
                else {
                    v[i] = r-i;
                    n = r+1;
                    m = i*2-n;
                }
            }
            while (m >= 0 and n < sz and s[m] == s[n]) {
                v[i]++;
                m--;
                n++;
            }
            if (i + v[i] > r) {
                c = i;
                r = i + v[i];
            }
        }
        return v;
    }

    std::string manacher(const std::string& s) {
        std::string separated = add_boundaries(s);
        int sz = separated.size();
        std::vector<int> v = compute_manacher(separated);

        
        int len = 0;
        int mid = 0;
        for (int i = 1; i < sz; i++) {
            if (len < v[i]) {
                len = v[i];
                mid = i;
            }
        }

        std::string res = separated.substr(mid-len, 2*len+1);
        return remove_boundaries(res);
    }
    
    std::vector<std::string> split(const std::string& text, const std::string& pattern) {
        std::vector<int> v = compute_kmp(pattern);
        std::vector<std::string> res;
        std::string curr = text;
        int pos;
        while (pos != -1) {
            pos = kmp(curr, pattern, v);
            if (pos == -1) {
                if (curr.size() != 0) res.push_back(curr);
            }
            else {
                if (pos != 0) res.push_back(std::string(curr, 0, pos));
                curr = std::string(curr, pos+pattern.size());
            }
        }
        return res;
    }
}

#endif
