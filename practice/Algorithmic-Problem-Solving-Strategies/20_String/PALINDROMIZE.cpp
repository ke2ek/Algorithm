// https://algospot.com/judge/problem/read/PALINDROMIZE
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector<int> getPartialMatch(const string &s) {
	int n = s.length();
	vector<int> pi(n, 0);
	int begin = 1, matched = 0;
	while (begin + matched < n) {
		if (s[begin + matched] == s[matched]) {
			++matched;
			pi[begin + matched - 1] = matched;
		} else {
			if (matched == 0) begin++;
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return pi;
}

int palindromize(string &s) {
	int n = s.size();
	string a = s;
	string b = s;
	reverse(b.begin(), b.end());
	vector<int> pi = getPartialMatch(b);
	int begin = 0, matched = 0;
	while (begin < n) {
		if (a[begin+matched] == b[matched]) {
			++matched;
			if (begin+matched == n) return matched;
		} else {
			if (matched == 0) begin++;
			else {
				begin += matched - pi[matched-1];
				matched = pi[matched-1];
			}
		}
	}
	return 0;
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		string s;
		cin >> s;
		cout << 2*s.size() - palindromize(s) << endl;
	}
	return 0;
}
