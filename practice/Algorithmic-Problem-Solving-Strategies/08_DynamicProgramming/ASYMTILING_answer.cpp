// https://algospot.com/judge/problem/read/ASYMTILING
#include <iostream>
#include <cstring>
#include <algorithm>
#define MOD 1000000007
using namespace std;

int n, cache[101];

int tiling(int width) {
    if (width <= 1) return 1;
    int &ret = cache[width];
    if (ret != -1) return ret;
    return ret = (tiling(width-2) + tiling(width-1)) % MOD;
}

// This function works by subtracting the # of symmetric tiling from the total # of tiling.
// Return the number of cases filling the rectangle of 2 * width.
int asymmetric(int width) {
    if (width & 1) // if width is odd,
        return (tiling(width) - tiling(width / 2) + MOD) % MOD;
    int ret = tiling(width);
    ret = (ret - tiling(width/2) + MOD) % MOD;
    ret = (ret - tiling(width/2 - 1) + MOD) % MOD;
    return ret;
}

int cache2[101];
// Count the # of asymmetric tiling directly.
int asymmetric2(int width) {
    if (width <= 2) return 0;
    int &ret = cache2[width];
    if (ret != -1) return ret;
    ret = asymmetric2(width-2) % MOD; // CASE 1) ||...||
    ret = (ret + asymmetric2(width-4)) % MOD; // CASE 2) |--|...|--|
    ret = (ret + tiling(width-3)) % MOD; // CASE 3) ||...|--|
    ret = (ret + tiling(width-3)) % MOD; // CASE 4) |--|...||
    return ret;
}

// O(n)
void solve() {
    memset(cache, -1, sizeof(cache));
    memset(cache2, -1, sizeof(cache2));
    cin >> n;
    // cout << asymmetric(n) << endl;
    cout << asymmetric2(n) << endl;
}

int main() {
    int tc;
    cin >> tc;
    while (tc--)
        solve();
    return 0;
}
