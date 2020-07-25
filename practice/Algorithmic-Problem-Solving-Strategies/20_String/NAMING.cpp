// https://algospot.com/judge/problem/read/NAMING
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> getPartialMatch(const string &N) {
	int m = N.size();
	vector<int> pi(m, 0);
	int begin = 1, matched = 0; // if begin == 0, find itself. (except!)
	while (begin + matched < m) {
		if (N[begin + matched] == N[matched]) {
			++matched;
			pi[begin + matched - 1] = matched;
		} else {
			if (matched == 0) ++begin;
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return pi;
}

vector<int> solve(const string &s) {
	vector<int> ret, pi = getPartialMatch(s);
	int k = s.size();
	while (k > 0) {
		ret.push_back(k);
		// find a needle in a substirng shorter than pushed (=included) length.
		k = pi[k-1];
	}
	return ret;
}

int main() {
	string a, b;
	cin >> a >> b;
	string s = a + b;
	vector<int> ret = solve(s);
	for (int i=ret.size()-1; i>=0; i--) {
		cout << ret[i] << " ";
	}
	cout << endl;
	return 0;
}
