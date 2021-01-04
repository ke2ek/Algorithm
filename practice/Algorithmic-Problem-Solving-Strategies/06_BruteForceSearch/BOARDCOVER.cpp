// https://algospot.com/judge/problem/read/BOARDCOVER#
#include <iostream>
#include <cstring>
#define MAXN 20
#define BLACK '#'
#define WHITE '.'
using namespace std;

const int dir[4][2][2] = {{{0,1},{1,0}},{{0,1},{1,1}},{{1,0},{1,1}},{{1,0},{1,-1}}};
int H, W;
char board[MAXN][MAXN];

int cover() {
    int y = -1, x = -1;
    bool b = true;
    for (int i = 0; i < H && b; i++)
        for (int j = 0; j < W && b; j++)
            if (board[i][j] == WHITE) {
                y = i; x = j; b = !b;
            }
    if (y == -1 && x == -1) return 1;
    
    board[y][x] = BLACK;
    int ret = 0;
    for (int t = 0; t < 4; t++) {
        int ny[2] = {y + dir[t][0][0], y + dir[t][1][0]};
        int nx[2] = {x + dir[t][0][1], x + dir[t][1][1]};
        
        if (ny[0] < 0 || ny[0] >= H || ny[1] < 0 || ny[1] >= H ||
            nx[0] < 0 || nx[0] >= W || nx[1] < 0 || nx[1] >= W)
            continue;
        if (board[ny[0]][nx[0]] == BLACK || board[ny[1]][nx[1]] == BLACK)
            continue;
        
        board[ny[0]][nx[0]] = board[ny[1]][nx[1]] = BLACK;
        ret += cover();
        board[ny[0]][nx[0]] = board[ny[1]][nx[1]] = WHITE;
    }
    board[y][x] = WHITE;
    return ret;
}

void solve() {
    cin >> H >> W;
    memset(board, 0, sizeof(board));
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            cin >> board[i][j];
    cout << cover() << endl;
}

int main() {
    int tc;
    cin >> tc;
    while (tc--)
        solve();
    return 0;
}