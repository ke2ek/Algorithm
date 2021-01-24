// https://algospot.com/judge/problem/read/NUMB3RS
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#define MAX_N 50
using namespace std;

int n, d, p, q;
vector<int> adj[MAX_N];
int degree[MAX_N];

double exhaustiveSearch(vector<int>& path) {
    if (path.size() == d+1) { // base case
        if (path.back() != q) return 0.0;
        double ret = 1.0;
        for (int i = 0; i+1 < path.size(); i++)
            ret /= degree[path[i]];
        return ret;
    }
    double ret = 0.0;
    for (auto there : adj[path.back()]) {
        path.push_back(there);
        ret += exhaustiveSearch(path);
        path.pop_back();
    }
    return ret;
}

// O(n^2 * d)
double cache[MAX_N][2*MAX_N];
double searchOptimized(int here, int days) {
    if (days == d) return (here == q ? 1.0 : 0.0);
    double &ret = cache[here][days];
    if (ret > -0.5) return ret;
    ret = 0.0;
    for (auto there : adj[here])
        ret += searchOptimized(there, days+1) / degree[here];
    return ret;
}

void solve() {
    cin >> n >> d >> p;
    for (int i = 0; i < n; i++) {
        adj[i].clear();
        degree[i] = 0;
    }

    for (int i = 0; i < n; i++)
        for (int j = 0, x; j < n; j++) {
            cin >> x;
            if (x) {
                adj[i].push_back(j);
                adj[j].push_back(i);
                degree[i]++;
                degree[j]++;
            }
        }
    int t;
    cin >> t;
    // vector<int> path(1, p);
    while (t--) {
        cin >> q;
        // printf("%.8f ", exhaustiveSearch(path));
        
        for (int i = 0; i < n; i++)
            for (int j = 0; j < d; j++)
                cache[i][j] = -0.5;
        printf("%.08lf ", searchOptimized(p, 0));
    }
    cout << endl;
}

int main() {
    int tc;
    cin >> tc;
    while (tc--)
        solve();
    return 0;
}
