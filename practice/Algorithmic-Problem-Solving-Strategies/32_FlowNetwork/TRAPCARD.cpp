// https://algospot.com/judge/problem/read/TRAPCARD
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;

int H, W;
int numA, numB; // Number of vertices in group A and group B.
vector<vector<bool> > graph;
vector<bool> visited;
// aMatch[a] = Number of vertex (in group A) matched with a.
// bMatch[b] = Number of vertex (in group B) matched with b.
vector<int> aMatch, bMatch;
// aChosen[i] = true if a is included in maximum independent set.
// bChosen[i] = true if b is included in maximum independent set.
vector<bool> aChosen, bChosen;
vector<vector<int> > vId; // vertex id at each room.

// Return true if there is an augmenting path
// from the vertex, a, in group A
// to vertices that have not been matched yet in group B.
bool dfs(int a) {
    if (visited[a]) return false;
    visited[a] = true;
    for (int b = 0; b < numB; b++) {
        if (graph[a][b]) {
            if (bMatch[b] == -1 || dfs(bMatch[b])) {
                aMatch[a] = b;
                bMatch[b] = a;
                return true;
            }
        }
    }
    return false;
}

// Return the size of matching
void bipartiteMatch() {
    aMatch = vector<int> (numA, -1);
    bMatch = vector<int> (numB, -1);
    for (int start = 0; start < numA; start++) {
        visited = vector<bool> (numA, false);
        dfs(start);
    }
}

// Calculate the maximum independent set.
void calcMaxIndependentSet() {
    // Calculate aMatch[], bMatchp[].
    bipartiteMatch();
    
    // First, select all vertices in A and unmatched vertices in B.
    aChosen = vector<bool> (numA, true);
    bChosen = vector<bool> (numB, false);
    for (int i = 0; i < numB; i++)
        if (bMatch[i] == -1)
            bChosen[i] = true;
    
    // Second, if two vertices are connected, exclude the vertex of A,
    // and select the matched vertex of B. Repeat until it does not have any change.
    while (true) {
        bool changed = false;
        for (int i = 0; i < numA; i++) {
            for (int j = 0; j < numB; j++) {
                if (aChosen[i] && bChosen[j] && graph[i][j]) {
                    assert(aMatch[i] != -1);
                    aChosen[i] = false;
                    bChosen[aMatch[i]] = true;
                    changed = true;
                }
            }
        }
        if (!changed) break;
    }
}

void makeBipartiteGraph(vector<string> &board) {
    int dy[] = { 1, -1, 0, 0 };
    int dx[] = { 0, 0, 1, -1 };
    vId = vector<vector<int> > (H, vector<int> (W, -1));
    
    // Set vId  at each room. (use even or odd idx for grid graph)
    numA = numB = 0;
    for (int y = 0; y < H; y++)
        for (int x = 0; x < W; x++)
            if (board[y][x] == '.')
                vId[y][x] = ((y + x) & 1) ? numA++ : numB++;
    
    // Check adjacency rooms.
    graph = vector<vector<bool> > (numA, vector<bool> (numB, false));
    for (int y = 0; y < H; y++)
        for (int x = 0; x < W; x++)
            if (((y + x) & 1) && board[y][x] == '.')
                for (int k = 0; k < 4; k++) {
                    int ny = y + dy[k];
                    int nx = x + dx[k];
                    if ((ny >= 0 && ny < H && nx >= 0 && nx < W)
                        && board[ny][nx] == '.')
                        graph[vId[y][x]][vId[ny][nx]] = true;
                }
}

void printMap(vector<string> &board) {
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            if (board[y][x] == '#') cout << '#';
            else if (vId[y][x] != -1) {
                if ((y + x) & 1) {
                    if (aChosen[vId[y][x]]) {
                        cout << '^'; continue;
                    }
                } else {
                    if (bChosen[vId[y][x]]) {
                        cout << '^'; continue;
                    }
                }
                cout << '.';
            }
        }
        cout << endl;
    }
}

void solve() {
    cin >> H >> W;
    vector<string> board(H);
    for (int i = 0; i < H; i++)
        cin >> board[i];
    makeBipartiteGraph(board);
    calcMaxIndependentSet();
    size_t cnt = count(aChosen.begin(), aChosen.end(), true);
    cnt += count(bChosen.begin(), bChosen.end(), true);
    cout << cnt << endl;
    printMap(board);
}

int main() {
    int tc;
    cin >> tc;
    while (tc--)
        solve();
    return 0;
}
