// https://algospot.com/judge/problem/read/FIRETRUCKS
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int V;
vector<vector<pair<int, int> > > adj;
const int INF = 987654321;

vector<int> dijkstra(int src) {
    vector<int> dist(V+1, INF);
    priority_queue<pair<int, int> > pq;
    dist[src] = 0;
    pq.push(make_pair(0, src));
    
    while (!pq.empty()) {
        int cost = -pq.top().first;
        int here = pq.top().second;
        pq.pop();
        
        if (dist[here] < cost) continue;
        
        for (int i=0; i<adj[here].size(); i++) {
            int there = adj[here][i].first;
            int nextDist = cost + adj[here][i].second;
            if (dist[there] > nextDist) {
                dist[there] = nextDist;
                pq.push(make_pair(-nextDist, there));
            }
        }
    }
    
    return dist;
}

void solve() {
    int e, n, m;
    cin >> V >> e >> n >> m;
    adj = vector<vector<pair<int, int> > > (V+1, vector<pair<int,int> > ());
    
    while (e--) {
        int src, dest, cost;
        cin >> src >> dest >> cost;
        adj[src].emplace_back(dest, cost);
        adj[dest].emplace_back(src, cost);
    }
    
    vector<int> firePlaces(n);
    vector<int> fireStations(m);
    for (int i=0; i<n; i++) cin >> firePlaces[i];
    for (int i=0; i<m; i++) {
        cin >> fireStations[i];
        // Add fake edge with zero cost.
        adj[0].emplace_back(fireStations[i], 0);
        adj[fireStations[i]].emplace_back(0, 0);
    }
    
    // Calculates all the shortes path.
    vector<int> ret = dijkstra(0);
    int sum = 0;
    for (int i=0; i<n; i++)
        sum += ret[firePlaces[i]];
    cout << sum << endl;
}

int main() {
    int tc;
    cin >> tc;
    while (tc--)
        solve();
    return 0;
}
