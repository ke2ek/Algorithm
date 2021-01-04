// https://algospot.com/judge/problem/read/CLOCKSYNC
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

const int INF = numeric_limits<int>::max();
const int deltas[3] = {3, 6, 9};
vector<int> switches[10] = {
    {0, 1, 2},
    {3, 7, 9, 11},
    {4, 10, 14, 15},
    {0, 4, 5, 6, 7},
    {6, 7, 8, 10, 12},
    {0, 2, 14, 15},
    {3, 14, 15},
    {4, 5, 7, 14, 15},
    {1, 2, 3, 4, 5},
    {3, 4, 5, 9, 13},
};
int clocks[16];
int best;

void go(int pos, int delta) {
    for (auto &j : switches[pos]) {
        clocks[j] = (clocks[j] + delta) % 12;
        if (clocks[j] == 0) clocks[j] = 12;
    }
}

void dfs(int pos, int cnt) {
    if (best < cnt) return;
    if (all_of(clocks, clocks + 16, [](int x){ return x == 12; })) {
        if (best > cnt) best = cnt;
        return;
    }
    if (pos == 10) return;
    
    dfs(pos + 1, cnt);
    for (int i = 0; i < 3; i++) {
        go(pos, deltas[i]);
        dfs(pos + 1, cnt + i + 1);
        go(pos, -deltas[i]);
    }
}

void solve() {
    for (int i = 0; i < 16; i++) cin >> clocks[i];
    best = INF;
    dfs(0, 0);
    cout << (best == INF ? -1 : best) << endl;
}

int main() {
    int tc;
    cin >> tc;
    while (tc--)
        solve();
    return 0;
}

