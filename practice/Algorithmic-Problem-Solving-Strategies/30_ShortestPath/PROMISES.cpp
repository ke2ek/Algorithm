// https://algospot.com/judge/problem/read/PROMISES
#include <iostream>
#include <vector>
#include <algorithm>
#define MAX_V 200
#define INF 987654321
using namespace std;

int V, M, N;
int adj[MAX_V][MAX_V];

void makeGraph() {
    cin >> V >> M >> N;
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            adj[i][j] = (i == j) ? 0 : INF;

    for (int i = 0; i < M; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        // Filter duplicate input.
        if (adj[a][b] > c)
            adj[a][b] = adj[b][a] = c;
    }
}

void floyd() {
    for (int k = 0; k < V; k++)
        for (int u = 0; u < V; u++)
            for (int v = 0; v < V; v++)
                adj[u][v] = min(adj[u][v], adj[u][k] + adj[k][v]);
}

bool update(int src, int dest, int cost) {
    if (adj[src][dest] <= cost) return false;
    for (int u = 0; u < V; u++) {
        for (int v = 0; v < V; v++) {
            adj[u][v] = min(adj[u][v], adj[u][src] + cost + adj[dest][v]);
            adj[u][v] = min(adj[u][v], adj[u][dest] + cost + adj[src][v]);
        }
    }
    return true;
}

// O(V^3 + V^2 * N)
void solve() {
    makeGraph();
    floyd();

    int useless = 0;
    while (N--) {
        int src, dest, cost;
        cin >> src >> dest >> cost;
        if (!update(src, dest, cost))
            useless++;
    }
    cout << useless << endl;
}

int main() {
    int tc;
    cin >> tc;
    while (tc--)
        solve();
    return 0;
}
