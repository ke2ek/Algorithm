// https://algospot.com/judge/problem/read/GALLERY
#include <iostream>
#include <vector>
using namespace std;

const int UNWATCHED = 0;
const int WATCHED = 1;
const int INSTALLED = 2;

int V;
vector<vector<int> > adj;
vector<bool> visited;
int installed;

int dfs(int here) {
    visited[here] = true;
    int children[3] = {0, 0, 0};
    for (int i=0; i<adj[here].size(); i++) {
        int there = adj[here][i];
        if (!visited[there])
            ++children[dfs(there)];
    }
    
    if (children[UNWATCHED]) {
        ++installed;
        return INSTALLED;
    }
    
    if (children[INSTALLED]) {
        return WATCHED;
    }
    return UNWATCHED;
}

int installCamera() {
    installed = 0;
    visited = vector<bool> (V, false);
    for(int u=0; u<V; u++)
        if (!visited[u] && dfs(u) == UNWATCHED)
            ++installed;
    return installed;
}

void solve() {
    int h;
    cin >> V >> h;
    adj = vector<vector<int> > (V, vector<int> ());
    for (int i=0; i<h; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    cout << installCamera() << endl;
}

int main() {
    int tc;
    cin >> tc;
    while (tc--)
        solve();
    return 0;
}
