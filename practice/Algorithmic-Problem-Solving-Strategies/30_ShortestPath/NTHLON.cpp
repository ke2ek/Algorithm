// https://algospot.com/judge/problem/read/NTHLON
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>
#include <queue>
#define START 399
#define INF 987654321
using namespace std;

// the number of vertices
int V;
// adj[i]: (dest verte number, edge weight) of i-th vertex
// edge weight means the expected time of A or B when passing the course.
vector<pair<int, int> > adj[400];

void makeGraph(const vector<int>& a, const vector<int>& b) {
    V = 400;
    for (int i = 0; i < V; i++) adj[i].clear();

    // add edges from the start point to others.
    for (int i = 0; i < a.size(); i++) {
        // difference of expected times between two player
        int diff = 199 + a[i] - b[i];
        adj[START].push_back(make_pair(diff, a[i]));
    }

    // add edges from each point to others.
    for (int vertex = 0; vertex < 399; vertex++) {
        for (int i = 0; i < a.size(); i++) {
            int next = vertex + a[i] - b[i];
            if (next < 0 || next >= 399) continue;
            adj[vertex].push_back(make_pair(next, a[i]));
        }
    }
}

vector<int> dijkstra(int src) {
    vector<int> dist(V, INF);
    priority_queue<pair<int, int> > pq;
    dist[src] = 0;
    pq.push(make_pair(0, src));
    while (!pq.empty()) {
        int cost = -pq.top().first;
        int here = pq.top().second;
        pq.pop();

        if (dist[here] < cost) continue;
        
        for (int i = 0; i < adj[here].size(); i++) {
            int there = adj[here][i].first;
            int nextDist = cost + adj[here][i].second;
            if (nextDist < dist[there]) {
                dist[there] = nextDist;
                pq.push(make_pair(-nextDist, there));
            }
        }
    }

    return dist;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++)
        cin >> a[i] >> b[i];
    makeGraph(a, b);
    vector<int> shortest = dijkstra(START);
    if (shortest[199] == INF) cout << "IMPOSSIBLE" << endl;
    else cout << shortest[199] << endl;
}

int main() {
    int tc;
    cin >> tc;
    while (tc--)
        solve();
    return 0;
}
