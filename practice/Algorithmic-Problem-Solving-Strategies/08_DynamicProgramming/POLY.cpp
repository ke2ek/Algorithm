// https://algospot.com/judge/problem/read/POLY
#include <iostream>
#include <cstring>
#include <algorithm>
#define MOD 10000000
using namespace std;

int n;
int cache[101][101];

// Return the # of polyominos
// when there were `l` squares in the previous line and `k` squares available.
// Notice that the # of vertical monotone polyominos in two lines is defined as
//      (# of squares in the first line) + (# of squares in the second line) - 1
int count(int l, int k) {
	if (k == 0) return 1; // base case
	int &ret = cache[l][k];
	if (ret != -1) return ret;
	ret = 0;
	for (int i=1; i<=k; i++)
		ret = (ret + (l + i - 1) * count(i, k-i)) % MOD;
	return ret;
}

// O(n^3)
void solve() {
    cin >> n;
    memset(cache, -1, sizeof(cache));
    int ans = 0;
    for (int i=1; i<=n; i++)
		ans = (ans + count(i, n-i)) % MOD;
    cout << ans << endl;
}

int main() {
    int tc;
    cin >> tc;
    while (tc--)
        solve();
    return 0;
}