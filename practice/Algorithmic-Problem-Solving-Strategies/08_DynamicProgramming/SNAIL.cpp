// https://algospot.com/judge/problem/read/SNAIL
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n, m;
double cache[1000][2000];

double climb(int days, int climbed) {
    if (days == m) return climbed >= n ? 1.0 : 0.0;
    double &ret = cache[days][climbed];
    if (ret != -1.0) return ret;
    return ret = 0.75 * climb(days+1, climbed+2) + 0.25 * climb(days+1, climbed+1);
}

void solve() {
    cin >> n >> m;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < 2*n; j++)
            cache[i][j] = -1.0;
    printf("%.010lf\n", climb(0, 0));
}

int main() {
    int tc;
    cin >> tc;
    while (tc--)
        solve();
    return 0;
}