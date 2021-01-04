// https://algospot.com/judge/problem/read/BOARDCOVER#
#include <iostream>
#include <vector>
using namespace std;

const int coverType[4][3][2] = {
    { {0, 0}, {1, 0}, {0, 1} }, // 
    { {0, 0}, {0, 1}, {1, 1} }, // ㄱ
    { {0, 0}, {1, 0}, {1, 1} }, // ㄴ
    { {0, 0}, {1, 0}, {1, -1} } // 
};

bool set(vector<vector<int>>& board, int y, int x, int type, int delta)
{
    bool ok = true;
    for (int i = 0; i < 3; i++) {
        const int ny = y + coverType[type][i][0];
        const int nx = x + coverType[type][i][1];
        if (ny < 0 || ny >= board.size() || nx < 0 || nx >= board[0].size())
            ok = false;
        else if ((board[ny][nx] += delta) > 1)
            ok = false; // if a tile duplicated
    }
    return ok;
}

int cover(vector<vector<int>>& board) {
    int y = -1, x = -1;
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            if (board[i][j] == 0) {
                y = i;
                x = j;
                break;
            }
        }
        if (y != -1) break;
    }
    if (y == -1) return 1; // base case
    int ret = 0;
    for (int type = 0; type < 4; type++) {
        if (set(board, y, x, type, 1))
            ret += cover(board);
        set(board, y, x, type, -1); // remove a tile
    }
    return ret;
}

void solve() {
    int H, W;
    cin >> H >> W;
    vector<vector<int>> board = vector<vector<int>> (H, vector<int> (W, 0));
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++) {
            char ch; cin >> ch;
            if (ch == '#') board[i][j] = 1;
        }
    cout << cover(board) << endl;
}

int main() {
    int tc;
    cin >> tc;
    while (tc--)
        solve();
    return 0;
}