// https://algospot.com/judge/problem/read/CHRISTMAS
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;

int N, K;
const int MOD = 20091101;

/* Time Limit Exceeded
void countOrder(vector<pair<int,int> > &orders, vector<int> &psum) {
	int n = psum.size();
	for (int i=0; i<n; i++) {
		for (int j=i+1; j<n; j++) {
			int sum = psum[j] - psum[i];
			if (sum % K == 0) {
				orders.push_back(make_pair(i,j));
			}
		}
	}
}

int getMaximumCount(vector<pair<int,int> > &orders, int pos, int a, int b) {
	if (pos == orders.size()) return 0;
	int ret = 0;
	int s = orders[pos].first;
	int e = orders[pos].second;
	if ((s <= a || s >= b) && (e <= a || e >= b)) {
		ret = max(ret, getMaximumCount(orders, pos+1, min(s,a), max(e,b)) + 1) % MOD;
	}
	ret = max(ret, getMaximumCount(orders, pos+1, a, b)) % MOD;
	return ret;
}
*/


// Return the number of method dividing toys to children fairly.
// Condition: (psum[b] - psum[a-1]) % K = 0 --> psum[b] % K == psum[a-1] % K --> psum[i] is defined as `(sum of range [0,i]) % K`
int waysToBuy(const vector<int> &psum) {
	int ret = 0;
	vector<long long> count(K, 0);
	for (int i=0; i<psum.size(); i++) {
		count[psum[i]]++; // Count the # of same values. (psum[b] % K == psum[a-1] % K)
	}

	for (int i=0; i<K; i++) {
		// Calculate the combination in case choosing range [a,b], which can be dividing toys to children fairly.
		// count[i] = the # of the number to be able to belong to the range [a,b]
		if (count[i] >= 2)
			ret = (ret + ((count[i] * (count[i] - 1)) / 2)) % MOD;
	}
	return ret;
}

// DP
int maxBuys(const vector<int> &psum) {
	// ret[i] = the maximum count of buying in the range [0,i]
	vector<int> ret(psum.size(), 0);
	// prev[s] = the last position when psum[] equals to s
	vector<int> prev(K, -1); 

	for (int i=0; i<psum.size(); i++) {
		// in case not including i-th toy box.
		if (i > 0) ret[i] = ret[i-1];
		else ret[i] = 0;

		// if psum[i] have even appeared in previous, buy from prev[psum[i]] + 1.
		int loc = prev[psum[i]];
		if (loc != -1) ret[i] = max(ret[i], ret[loc] + 1);

		// Update the last position and require to maximize the number of ranges for a possible smaller range.
		prev[psum[i]] = i; // Save the current position.
	}
	return ret.back();
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &N, &K);

		vector<int> psum(N+1, 0);
		for (int i=0; i<N; i++) {
			int x;
			scanf("%d", &x);
			//psum[i+1] = psum[i] + x;
			psum[i+1] = (psum[i] + x) % K;
		}

		/*
		vector<pair<int,int> > orders;
		countOrder(orders, psum);
		printf("%d %d\n", (int)orders.size(), getMaximumCount(orders, 0, N, -1));
		*/
		printf("%d %d\n", waysToBuy(psum), maxBuys(psum));
	}
	return 0;
}
