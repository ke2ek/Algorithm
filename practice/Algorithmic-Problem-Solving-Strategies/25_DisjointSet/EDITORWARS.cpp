// https://algospot.com/judge/problem/read/EDITORWARS
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct BipartiteUnionFind {
    vector<int> parent; // parent node of i-th
    vector<int> rank; // the rank of tree having i-th node as the root
    vector<int> enemy; // root node of enemy set of tree having i-th node as the root
    vector<int> size; // the size of tree having i-th node as the root
    
    BipartiteUnionFind(int n)
    : parent(n), rank(n, 1), enemy(n, -1), size(n, 1)
    {
        for (int i=0; i<n; i++)
            parent[i] = i;
    }
    
    int find(int u) {
        if (parent[u] == u) return u;
        return parent[u] = find(parent[u]);
    }
    
    int merge(int u, int v) {
        // base case: empty set
        if (u == -1 || v == -1) return max(u, v);
        u = find(u);
        v = find(v);
        if (u == v) return u;
        if (rank[u] > rank[v]) swap(u, v);
        if (rank[u] == rank[v]) rank[v]++;
        parent[u] = v;
        size[v] += size[u];
        return v;
    }
    
    bool dis(int u, int v) {
        u = find(u);
        v = find(v);
        // if both are always comrade, then true
        if (u == v) return false;
        // The enemy of my enemy is my comrade.
        int a = merge(u, enemy[v]);
        int b = merge(v, enemy[u]);
        enemy[a] = b;
        enemy[b] = a;
        return true;
    }
    
    bool ack(int u, int v) {
        u = find(u);
        v = find(v);
        // if both are enemy each other, then false
        if (enemy[u] == v) return false;
        // The enemy of my comrade is my enemy.
        int a = merge(u, v);
        int b = merge(enemy[u], enemy[v]);
        enemy[a] = b;
        // if there is not an enemy
        if (b != -1) enemy[b] = a;
        return true;
    }
};

int maxParty(const BipartiteUnionFind& buf, int n) {
    int ret = 0;
    for (int node=0; node<n; node++) {
        if (buf.parent[node] == node) {
            int enemy = buf.enemy[node];
            // to avoid counting duplicated subsets, only work if enemy < node
            // count only one if enemy == -1
            if (enemy > node) continue;
            int mySize = buf.size[node];
            int enemySize = (enemy == -1 ? 0 : buf.size[enemy]);
            // add the larger set
            ret += max(mySize, enemySize);
        }
    }
    return ret;
}

void solve() {
    int n, m;
    cin >> n >> m;
    BipartiteUnionFind buf(n);
    int contradict = -1;
    for (int i=0; i<m; i++) {
        string s;
        int a, b;
        cin >> s >> a >> b;
        if (contradict != -1) continue;
        if ((s.compare("ACK") == 0) && !buf.ack(a, b)) {
            contradict = i+1;
        }
        if ((s.compare("DIS") == 0) && !buf.dis(a, b)) {
            contradict = i+1;
        }
    }
    
    if (contradict == -1) {
        cout << "MAX PARTY SIZE IS " << maxParty(buf, n) << endl;
    } else {
        cout << "CONTRADICTION AT " << contradict << endl;
    }
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
