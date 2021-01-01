// https://algospot.com/judge/problem/read/PICNIC
#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<pair<int,int>> friends;
vector<bool> visited;

int countPair(int pos, int cnt) {
    if (pos == m) {
        if (cnt == n) return 1;
        return 0;
    }
    int ret = countPair(pos + 1, cnt);
    if (!visited[friends[pos].first] and !visited[friends[pos].second]) {
        visited[friends[pos].first] = true;
        visited[friends[pos].second] = true;
        ret += countPair(pos + 1, cnt + 2);
        visited[friends[pos].first] = false;
        visited[friends[pos].second] = false;
    }
    return ret;
}

void solve() {
    cin >> n >> m;
    friends = vector<pair<int, int>> (m);
    visited = vector<bool> (n, false);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        friends[i] = make_pair(a, b);
    }
    cout << countPair(0,0) << endl;
}

int main() {
    int tc;
    cin >> tc;
    while (tc--)
        solve();
    return 0;
}
