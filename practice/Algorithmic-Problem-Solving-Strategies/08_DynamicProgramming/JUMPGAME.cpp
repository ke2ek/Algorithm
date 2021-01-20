// https://algospot.com/judge/problem/read/JUMPGAME
#include <iostream>
#include <cstring>
#include <vector>
#define MAX_N 100
using namespace std;

int N;
int cache[MAX_N][MAX_N];
int board[MAX_N][MAX_N];

bool jump(int y, int x) {
    if (y >= N or x >= N) return false;
    if (y == N-1 and x == N-1) return true;
    int &ret = cache[y][x];
    if (ret != -1) return ret;
    return ret = jump(y + board[y][x], x) or jump(y, x + board[y][x]);
}

void solve() {
    cin >> N;
    memset(cache, -1, sizeof(cache));
    memset(board, 0, sizeof(board));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> board[i][j];
    cout << (jump(0, 0) ? "YES" : "NO") << endl;
}

int main() {
    int tc;
    cin >> tc;
    while (tc--)
        solve();
    return 0;
}
