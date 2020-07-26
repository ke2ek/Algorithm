// https://algospot.com/judge/problem/read/JAEHASAFE
#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> getPartialMatch(const string &s) {
	int n = s.size();
	vector<int> pi(n, 0);
	int begin = 1, matched = 0;
	while (begin + matched < n) {
		if (s[begin + matched] == s[matched]) {
			matched++;
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


vector<int> kmsSearch(const string &H, const string &N) {
	int h = H.size(), n = N.size();
	vector<int> ret, pi = getPartialMatch(N);
	int begin = 0, matched = 0;
	while (begin < h - n) {
		if (matched < n && H[begin + matched] == N[matched]) {
			matched++;
			if (matched == n) ret.push_back(begin);
		} else {
			if (matched == 0) begin++;
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return ret;
}


// Anti-clockwise direction
int shifts(const string &original, const string &target) {
	return kmsSearch(original + original, target)[0];
}


int solve(vector<string> &v) {
	int ret = 0;
	bool clockwise = true;
	for (int i=1; i<v.size(); i++) {
		if (clockwise) ret += shifts(v[i], v[i-1]);
		else ret += shifts(v[i-1], v[i]);
		clockwise = !clockwise;
	}
	return ret;
}


int main() {
	int T;
	cin >> T;
	while (T--) {
		int N;
		cin >> N;
		vector<string> dials(N+1);
		for (int i=0; i<=N; i++) cin >> dials[i];
		cout << solve(dials) << endl;
	}
	return 0;
}
