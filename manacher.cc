// Manacher's algorithm: Longest palindromic substring in O(n) time.

#include <iostream>
#include <string>
#include <vector>
using namespace std;

const char SEP = '|';

string add_boundaries(string& s) {
	int n = s.size();
	string s2(2*n+1, ' ');
	for (int i = 0; i < n; i++) {
		s2[2*i] = SEP;
		s2[2*i + 1] = s[i];
	}
	s2[2*n] = SEP;
	return s2;
}

string remove_boundaries(string& s) {
	int n = s.size();
	string s2(n/2, ' ');
	for (int i = 0; i < n/2; i++) {
		s2[i] = s[2*i+1];
	}
	return s2;
}

string manacher(string& s) {
	string s2 = add_boundaries(s);
	cout << s2 << endl;
	cout << remove_boundaries(s2) << endl;
	int sz = s2.size();
	
	vector<int> v(sz);
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
		while (m >= 0 and n < sz and s2[m] == s2[n]) {
			v[i]++;
			m--;
			n++;
		}
		if (i + v[i] > r) {
			c = i;
			r = i + v[i];
		}
	}
	
	int len = 0;
	c = 0;
	for (int i = 1; i < sz; i++) {
		if (len < v[i]) {
			len = v[i];
			c = i;
		}
	}
	for (auto x : s2) cout << x << " ";
	cout << endl;
	for (auto x : v) cout << x << " ";
	cout << endl;
	string ss = s2.substr(c-len, 2*len+1);
	return remove_boundaries(ss);
}

int main() {
	string text;
	cout << "Enter text: ";
	cin >> text;
	cout << manacher(text) << endl;
}
