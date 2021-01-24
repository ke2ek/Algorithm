// https://algospot.com/judge/problem/read/LIS
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int N;
int seq[501];
int cache[501];

// O(N^2)
int maxLIS(int pos) {
    int &ret = cache[pos];
    if (ret != -1) return ret;
    ret = 1;
    for (int i = pos + 1; i <= N; i++)
        if (seq[pos] < seq[i])
            ret = max(ret, maxLIS(i) + 1);
    return ret;
}

void solve() {
    cin >> N;
    memset(cache, -1, sizeof(cache));
    seq[0] = 0;
    for (int i = 1; i <= N; i++) cin >> seq[i];
    cout << maxLIS(0) - 1 << endl;
}

int main() {
    int tc;
    cin >> tc;
    while (tc--)
        solve();
    return 0;
}