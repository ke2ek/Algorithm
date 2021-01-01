// https://algospot.com/judge/problem/read/BOGGLE
#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int dx[8] = {0, -1, 1, 0, 1, -1, 1, -1};
const int dy[8] = {1, -1, 1, -1, -1, 1, 0, 0};
char board[5][5];

// Time limit exceeded.
bool bruteForce(int y, int x, string &word, int pos) {
    if (pos == word.size() - 1) return word[pos] == board[y][x];
    if (word[pos] == board[y][x]) {
        for (int i = 0; i < 8; i++) {
            int ny = y + dy[i];
            int nx = x + dx[i];
            if (nx < 0 or nx >= 5 or ny < 0 or ny >= 5) continue;
            if (bruteForce(ny, nx, word, pos + 1)) return true;
        }
    }
    return false;
}

bool hasWord(string &word) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (bruteForce(i, j, word, 0))
                return true;
        }
    }
    return false;
}


void solve() {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            cin >> board[i][j];
    
    int N;
    cin >> N;
    string word;
    for (int i = 0; i < N; i++) {
        cin >> word;
        cout << word << " " << (hasWord(word) ? "YES" : "NO") << endl;
    }
}

int main() {
    int tc;
    cin >> tc;
    while (tc--)
        solve();
    return 0;
}
