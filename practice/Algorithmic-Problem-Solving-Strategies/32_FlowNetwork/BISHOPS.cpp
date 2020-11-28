// https://algospot.com/judge/problem/read/BISHOPS
#include <iostream>
#include <vector>
using namespace std;

int N;
int numA, numB; // Number of vertices in group A and group B.
vector<vector<bool> > graph;
vector<int> aMatch, bMatch;
vector<bool> visited;


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
int bipartiteMatch() {
    aMatch = vector<int> (numA, -1);
    bMatch = vector<int> (numB, -1);
    int size = 0;
    for (int start = 0; start < numA; start++) {
        visited = vector<bool> (numA, false);
        if (dfs(start)) size++;
    }
    return size;
}

// Make bipartite graph from the given board.
void makeBipartiteGraph(vector<string> &board) {
    // diagonal right-top-to-left-bottom and left-top-to-right-bottom
    int dy[2] = { -1, 1 };
    int dx[2] = { 1, 1, };
    
    // gId[dir][y][x] = On the direction, the group number that (y, x) belongs to
    vector<vector<int> > gId[2];
    gId[0] = vector<vector<int> > (N, vector<int> (N, -1));
    gId[1] = vector<vector<int> > (N, vector<int> (N, -1));
    int count[2] = {0, 0}; // Number of vertices in each group.
    for (int dir = 0; dir < 2; dir++)
        for (int y = 0; y < N; y++)
            for (int x = 0; x < N; x++)
                if (board[y][x] == '.' && gId[dir][y][x] == -1) {
                    int ny = y, nx = x;
                    // Count group id that (y, x) and adjacency vertices belongs to.
                    while ((ny >= 0 && ny < N && nx >= 0 && nx < N)
                           && board[ny][nx] == '.')
                    {
                        gId[dir][ny][nx] = count[dir];
                        ny += dy[dir];
                        nx += dx[dir];
                    }
                    count[dir]++;
                }
    
    numA = count[0];
    numB = count[1];
    graph = vector<vector<bool> > (numA, vector<bool> (numB, false));
    for (int y = 0; y < N; y++)
        for (int x = 0; x < N; x++)
            if (board[y][x] == '.')
                graph[gId[0][y][x]][gId[1][y][x]] = true;
}

void solve() {
    cin >> N;
    vector<string> board(N);
    for (int i = 0; i < N; i++)
        cin >> board[i];
    makeBipartiteGraph(board);
    cout << bipartiteMatch() << endl;
}

int main() {
    int tc;
    cin >> tc;
    while (tc--)
        solve();
    return 0;
}

