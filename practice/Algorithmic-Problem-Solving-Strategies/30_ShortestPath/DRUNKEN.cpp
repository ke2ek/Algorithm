// https://algospot.com/judge/problem/read/DRUNKEN
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#define MAX_V 500
#define INF 987654321
using namespace std;

int V, E;
int delay[MAX_V];
int adj[MAX_V][MAX_V];
int W[MAX_V][MAX_V];

void makeGraph() {
    cin >> V >> E;
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            adj[i][j] = W[i][j] = INF;
    for (int i = 0; i < V; i++)
        cin >> delay[i];
    for (int i = 0; i < E; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a-1][b-1] = adj[b-1][a-1] = c;
    }
}

void floyd() {
    // Sort every vertices by delay time ascending.
    // because thie problem needs to satisfy Optimal Substructure in Dynamic Programming.
    vector<pair<int, int> > sortedDelay;
    for (int i = 0; i < V; i++)
        sortedDelay.push_back(make_pair(delay[i], i));
    sort(sortedDelay.begin(), sortedDelay.end());

    // Initialize W.
    for (int u = 0; u < V; u++)
        for (int v = 0; v < V; v++)
            W[u][v] = (u == v) ? 0 : adj[u][v];
    
    // Calculate the shortest path via `w`.
    for (int k = 0; k < V; k++) {
        int w = sortedDelay[k].second;
        for (int u = 0; u < V; u++) {
            for (int v = 0; v < V; v++) {
                adj[u][v] = min(adj[u][v], adj[u][w] + adj[w][v]);
                W[u][v] = min(W[u][v], adj[u][w] + adj[w][v] + delay[w]);
            }
        }
    }
}

int main() {
    makeGraph();
    floyd();
    int tc;
    cin >> tc;
    while (tc--) {
        int src, dest;
        cin >> src >> dest;
        cout << W[src-1][dest-1] << endl;
    }
    return 0;
}
