// https://algospot.com/judge/problem/read/TRIPATHCNT
#include <iostream>
#include <cstring>
#include <algorithm>
#include <utility>
using namespace std;

int n;
int tri[100][100];
pair<int,int> cache[100][100];

pair<int,int> pathCount(int y, int x) {
    if (y == n-1) return pair<int,int> (tri[y][x], 1);
    auto &ret = cache[y][x];
    if (ret.first != -1) return ret;
    pair<int,int> a = pathCount(y+1, x), b = pathCount(y+1, x+1);
    if (a.first > b.first) ret = a;
    else if (a.first < b.first) ret = b;
    else { a.second += b.second; ret = a; }
    ret.first += tri[y][x];
    return ret;
}

// 28ms
void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            cin >> tri[i][j];
            cache[i][j] = pair<int,int> (-1,-1);
        }
    }
    pair<int,int> ans = pathCount(0, 0);
    cout << ans.second << endl;
}

int main() {
    int tc;
    cin >> tc;
    while (tc--)
        solve();
    return 0;
}