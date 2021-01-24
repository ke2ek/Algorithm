// https://algospot.com/judge/problem/read/TILING2
#include <iostream>
#include <cstring>
#include <algorithm>
#define MOD 1000000007
using namespace std;

// O(n)
void solve() {
    int n; cin >> n;
    int dp[100];
  	dp[0]=1; dp[1]=2;
    for (int i = 2; i < n; i++)
        dp[i] = (dp[i-1] + dp[i-2]) % MOD;
    cout << dp[n-1] << endl;
}

int main() {
    int tc;
    cin >> tc;
    while (tc--)
        solve();
    return 0;
}
