// https://algospot.com/judge/problem/read/ROUTING
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

int N, M;
vector<vector<pair<int, double> > > adj;
const double INF = 987654321.0;

vector<double> dijkstra(int src) {
    vector<double> dist(N, INF);
    priority_queue<pair<double, int> > pq;
    dist[src] = 0.0;
    pq.push(make_pair(0.0, src));
    
    while (!pq.empty()) {
        double cost = -pq.top().first;
        int here = pq.top().second;
        pq.pop();

        if (dist[here] < cost) continue;

        for (int i=0; i<adj[here].size(); i++) {
            int there = adj[here][i].first;
            double nextDist = cost + log(adj[here][i].second);
            if (dist[there] > nextDist) {
                dist[there] = nextDist;
                pq.push(make_pair(-nextDist, there));
            }
        }
    }

    return dist;
}

int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> N >> M;
        adj = vector<vector<pair<int, double> > > (N, vector<pair<int, double> > ());
        while (M--) {
            int src, dest;
            double cost;
            cin >> src >> dest >> cost;
            adj[src].push_back(make_pair(dest, cost));
            adj[dest].push_back(make_pair(src, cost));
        }
        vector<double> ret = dijkstra(0);
        printf("%.10lf\n", exp(ret[N-1]));
    }
    return 0;
}