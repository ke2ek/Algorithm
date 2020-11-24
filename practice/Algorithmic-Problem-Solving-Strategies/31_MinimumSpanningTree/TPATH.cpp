// https://algospot.com/judge/problem/read/TPATH
#include <iostream>
#include <vector>
#include <algorithm>
#define INF 987654321
using namespace std;

// # of vertices, # of edges
int V, E;
vector<pair<int, pair<int, int> > > edges; // graph
vector<int> weights;

struct DisjointSet {
    vector<int> parent, rank;

    DisjointSet(int n) : parent(n), rank(n, 1) {
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int u) {
        if (parent[u] == u) return u;
        return parent[u] = find(parent[u]); // except duplicate operation
    }

    void merge(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return;
        if (rank[u] > rank[v]) swap(u, v);
        // always rank[u] <= rank[v], where rank means the height of each tree.
        parent[u] = v;
        if (rank[u] == rank[v]) rank[v]++;
    }
};

int kruskalMinUpperBound(int low) {
    DisjointSet sets(V);
    for (int i = 0; i < edges.size(); i++) {
        if (edges[i].first < weights[low]) continue;
        // Add edges[i] to the MST.
        sets.merge(edges[i].second.first, edges[i].second.second);
        // Return the last-added weight if the source and the destination were connected.
        if (sets.find(0) == sets.find(V - 1))
            return edges[i].first; // the upper bound
    }
    return INF;
}


void solve() {
    cin >> V >> E;
    weights = vector<int> (E);
    edges = vector<pair<int, pair<int, int> > > (E);
    for (int i = 0; i < E; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        edges.push_back({c, {a, b}});
        weights[i] = c;
    }
    sort(edges.begin(), edges.end());
    
    // O(E^2)
    int minDiff = INF;
    for (int i = 0; i < weights.size(); i++)
        minDiff = min(minDiff, kruskalMinUpperBound(i) - weights[i]);
    cout << minDiff << endl;
}

int main() {
    int tc;
    cin >> tc;
    while (tc--)
        solve();
    return 0;
}
