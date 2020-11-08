// https://algospot.com/judge/problem/read/LAN
#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#define MAX_V 500
#define INF 987654321
using namespace std;

struct DisjointSet {
    vector<int> parent, rank;

    DisjointSet(int n) : parent(n), rank(n, 1) {
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int u) {
        if (parent[u] == u) return u;
        return parent[u] = find(parent[u]);
    }

    void merge(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return;
        if (rank[u] > rank[v]) swap(u, v);
        parent[u] = v;
        if (rank[u] == rank[v]) rank[v]++;
    }
};

int N, M;
vector<pair<int, int> > coord;
vector<pair<int, double> > adj[MAX_V];

double dist(pair<int, int>& u, pair<int, int>& v) {
    int x1 = u.first, y1 = u.second;
    int x2 = v.first, y2 = v.second;
    return sqrt(pow(x2 - x1, 2) +  powf(y2 - y1, 2) * 1.0);
}

void makeGraph() {
    cin >> N >> M;
    coord = vector<pair<int, int> > (N);
    for (int i = 0; i < N; i++) {
        adj[i].clear();
        cin >> coord[i].first;
    }
    for (int i = 0; i < N; i++)
        cin >> coord[i].second;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (i != j)
                adj[i].push_back(make_pair(j, dist(coord[i], coord[j])));
}

double kruskal() {
    double ret = 0;
    vector<pair<double, pair<int, int> > > edges;
    for (int u = 0; u < N; u++) {
        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i].first;
            double weight = adj[u][i].second;
            edges.push_back(make_pair(weight, make_pair(u, v)));
        }
    }
    sort(edges.begin(), edges.end());
    DisjointSet sets(N);
    for (int i = 0; i < edges.size(); i++) {
        double cost = edges[i].first;
        int u = edges[i].second.first;
        int v = edges[i].second.second;
        if (sets.find(u) == sets.find(v)) continue;
        sets.merge(u, v);
        ret += cost;
    }
    return ret;
}

void solve() {
    makeGraph();
    for (int i = 0; i < M; i++) {
        int src, dest;
        cin >> src >> dest;
        for (int j = 0; j < adj[src].size(); j++) {
            int v = adj[src][j].first;
            if (v == dest)
                adj[src][j].second = 0.0;
        }
    }
    printf("%.10lf\n", kruskal());
}

int main() {
    int tc;
    cin >> tc;
    while (tc--)
        solve();
    return 0;
}
