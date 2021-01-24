// https://algospot.com/judge/problem/read/JLIS
#include <iostream>
#include <cstring>
#include <limits>
#include <algorithm>
#define MAX_N 101
using namespace std;

int n, m;
long long A[MAX_N], B[MAX_N];
int cache[MAX_N][MAX_N];

int JLIS(int pos1, int pos2) {
    int &ret = cache[pos1][pos2];
    if (ret != -1) return ret;
    ret = 1;
    int i = pos1 + 1, j = pos2 + 1;
    while (i <= n or j <= m) {
        if (i <= n and A[pos1] < A[i] and B[pos2] < A[i])
            ret = max(ret, JLIS(i, pos2) + 1);
        if (j <= m and A[pos1] < B[j] and B[pos2] < B[j])
            ret = max(ret, JLIS(pos1, j) + 1);
        i++; j++;
    }
    return ret;
}

void solve() {
    cin >> n >> m;
    A[0] = B[0] = numeric_limits<long long>::min();
    for (int i = 1; i <= n; i++) cin >> A[i];
    for (int i = 1; i <= m; i++) cin >> B[i];
    memset(cache, -1, sizeof(cache));
    cout << JLIS(0, 0) - 1 << endl;
}

int main() {
    int tc;
    cin >> tc;
    while (tc--)
        solve();
    return 0;
}