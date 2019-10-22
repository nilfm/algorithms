// KMP algorithm - Find an occurrence of pattern in text in O(n) time.

#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> compute(string& s) {
    int n = s.size();
    vector<int> v(n);
    int i = 1, j = 0;
    v[0] = 0;
    while (i < n) {
        if (s[i] == s[j]) {
            v[i] = v[i-1] + 1;
            i++;
            j++;
        }
        else {
            while (s[i] != s[j] and j > 0) {
                j = v[j-1];
            }
            if (s[i] == s[j]) {
                v[i] = v[j] + 1;
            }
            else v[i] = 0;
            i++;
        }
    }
    return v;
}

int compare(string& s, string& p) {
    vector<int> v = compute(p);
    int m = s.size();
    int n = p.size();
    int i = 0, j = 0;
    while (i < m) {
        if (s[i] == p[j]) {
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

int main() {
    string pattern;
    cout << "Enter pattern: ";
    cin >> pattern;
    string text;
    cout << "Enter text: ";
    cin >> text;
    cout << compare(text, pattern) << endl;
}
