// https://algospot.com/judge/problem/read/TRIPATHCNT
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int n, triangle[100][100];
int cache[100][100];

// Return the maximum sum of the path from (y, x) to the bottom line.
int path(int y, int x) {
    if (y == n-1) return triangle[y][x];
    int &ret = cache[y][x];
    if (ret != -1) return ret;
    return ret = max(path(y+1, x), path(y+1, x+1)) + triangle[y][x];
}

int countCache[100][100];

// Return the number of paths with the maximum sum from (y, x) to the bottom line.
int count(int y, int x) {
    if (y == n-1) return 1;
    int &ret = countCache[y][x];
    if (ret != -1) return ret;
    ret = 0;
    if (path(y+1, x+1) >= path(y+1, x)) ret += count(y+1, x+1);
    if (path(y+1, x+1) <= path(y+1, x)) ret += count(y+1, x);
    return ret;
}

// 44ms
void solve() {
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= i; j++)
            cin >> triangle[i][j];
    memset(cache, -1, sizeof(cache));
    memset(countCache, -1, sizeof(countCache));
    cout << count(0,0) << endl;
}

int main() {
    int tc;
    cin >> tc;
    while (tc--)
        solve();
    return 0;
}