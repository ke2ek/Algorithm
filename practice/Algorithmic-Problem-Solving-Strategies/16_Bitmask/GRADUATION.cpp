// https://algospot.com/judge/problem/read/GRADUATION
#include <iostream>
#include <algorithm>
#include <string.h>
#define MAXN 12
using namespace std;

const int INF = 987654321;
int N;	// # of total subjects
int K;	// # of subjects to take
int M;	// # of semesters
int L;	// maximum # of subjects to take in a semester

// prerequisite[i] = set of the prerequisite in each subject
int prerequisite[MAXN];
// classes[i] = set of the opening subjects in each semester
int classes[10];
// cache[i][bitset] = mimimum # of the required semesters when subset `bitset` is taken, in i-th semester
int cache[10][1<<MAXN];

// Return the number of 1 bit
int bitCount(int n) {
	return __builtin_popcount(n);
	/*
	int ret = 0;
	for (int i=0; i<N; i++) {
		if ((n & (1 << i)) != 0) ret++;
	}
	return ret;
	*/
}

int graduate(int semester, int taken) {
	// base case
	if (bitCount(taken) >= K) return 0;
	if (semester == M) return INF;

	int &ret = cache[semester][taken];
	if (ret != -1) return ret;

	ret = INF;
	int canTake = (classes[semester] & ~taken); // Not yet learn.

	// Abandon subjects which don't satisfy the prerequisite.
	for (int i = 0; i < N; i++) {
		if ((canTake & (1 << i)) && (taken & prerequisite[i]) != prerequisite[i])
			canTake &= ~(1 << i); // exclude
	}

	// Visit all subset.
	for (int take = canTake; take > 0; take = ((take - 1) & canTake)) {
		if (bitCount(take) > L) continue;
		ret = min(ret, graduate(semester + 1, taken | take) + 1);
	}

	// In case nothing taken.
	ret = min(ret, graduate(semester + 1, taken));
	return ret;
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		int cnt, subject;
		cin >> N >> K >> M >> L;
		for (int i=0; i<N; i++) {
			cin >> cnt;
			prerequisite[i] = 0;
			for (int j=0; j<cnt; j++) {
				cin >> subject;
				prerequisite[i] |= (1 << subject);
			}
		}
		for (int i=0; i<M; i++) {
			cin >> cnt;
			classes[i] = 0;
			for (int j=0; j<cnt; j++) {
				cin >> subject;
				classes[i] |= (1 << subject);
			}
		}
		memset(cache, -1, sizeof(cache));
		int ret = graduate(0, 0);
		if (ret == INF) cout << "IMPOSSIBLE" << endl;
		else cout << ret << endl;
	}
	return 0;
}
