// https://algospot.com/judge/problem/read/TRIANGLEPATH
#include <iostream>
#include <cstring>
#include <algorithm>
#define MAX_N 100
using namespace std;

int n;
int triangle[MAX_N][MAX_N];
int cache[MAX_N][MAX_N];

// Exhaustive Search -> Timie Limit Exceeded
int search(int y, int x) {
    if (y == n) return 0;
    return max(search(y+1, x), search(y+1, x+1)) + triangle[y][x];
}

// Top-Down
int searchOptimized(int y, int x) {
    if (y == n) return 0;
    int &ret = cache[y][x];
    if (ret != -1) return ret;
    return ret = max(searchOptimized(y+1, x), searchOptimized(y+1, x+1)) + triangle[y][x];
}

// Bottom-Up
int searchOptimized2() {
    cache[0][0] = triangle[0][0];
    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            if (j > 0) cache[i][j] = max(cache[i][j], cache[i-1][j-1] + triangle[i][j]);
            cache[i][j] = max(cache[i][j], cache[i-1][j] + triangle[i][j]);
        }
    }
    return *max_element(cache[n-1], cache[n-1]+n);
}

void solve() {
    cin >> n;
    memset(triangle, -1, sizeof(triangle));
    memset(cache, -1, sizeof(cache));
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= i; j++)
            cin >> triangle[i][j];
    // cout << search(0, 0) << endl;
    cout << searchOptimized(0, 0) << endl;
    // cout << searchOptimized2() << endl;
}

int main() {
    int tc;
    cin >> tc;
    while (tc--)
        solve();
    return 0;
}
