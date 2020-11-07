// https://algospot.com/judge/problem/read/TIMETRIP
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define INF 987654321
using namespace std;

int V, W;
vector<pair<int, int> > adj[100];

// Return the length of the shortest path from src to dest.
int getPathWithBellmanFord(int src, int dest, int sign) {
    vector<int> upper(V, INF);
    bool relaxed;
    upper[src] = 0;
    for (int iter = 0; iter < V; iter++) {
        relaxed = false;
        for (int here = 0; here < V; here++) {
            // To find the cycle in the path from src to dest, skip uninitialized edges.
            if (upper[here] == INF) continue;
            for (int i = 0; i < adj[here].size(); i++) {
                int there = adj[here][i].first;
                int cost = upper[here] + adj[here][i].second * sign;
                if (upper[there] > cost) {
                    relaxed = true;
                    upper[there] = cost;
                }
            }
        }
        // Already approximated, so do not need to look at other points.
        if (!relaxed) break;
        // Found cycle!
        if (iter == V - 1) return -INF;
    }
    return upper[dest];
}

void solve() {
    cin >> V >> W;
    for (int i = 0; i < 100; i++) adj[i].clear();
    for (int i = 0; i < W; i++) {
        int a, b, d;
        cin >> a >> b >> d;
        adj[a].push_back(make_pair(b, d));
    }

    int length = getPathWithBellmanFord(0, 1, 1);
    if (length == -INF) {
        cout << "INFINITY ";
    } else if (length == INF) {
        cout << "UNREACHABLE" << endl;
        return;
    } else {
        cout << length << " ";
    }

    length = getPathWithBellmanFord(0, 1, -1);
    if (length == -INF) {
        cout << "INFINITY" << endl;
    } else {
        cout << (length * -1) << endl;
    }
}

int main() {
    int tc;
    cin >> tc;
    while (tc--)
        solve();
    return 0;
}
