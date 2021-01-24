// https://algospot.com/judge/problem/read/ASYMTILING
#include <iostream>
#include <cstring>
#include <algorithm>
#define MOD 1000000007
using namespace std;

// O(n)
void solve() {
    int n, dp1[100], dp2[100];
    cin >> n;
    dp1[0] = dp2[0] = dp2[2] = 1;
    dp1[1] = dp2[1] = 2;
    dp1[2] = dp2[3] = 3;
    dp1[3] = 5;
    for (int i = 4; i < n; i++) {
        dp1[i] = (dp1[i-1] + dp1[i-2]) % MOD;
        dp2[i] = (dp2[i-2] + dp2[i-4]) % MOD;
    }
    cout << (dp1[n-1] + MOD - dp2[n-1]) % MOD << endl;
}

int main() {
    int tc;
    cin >> tc;
    while (tc--)
        solve();
    return 0;
}
