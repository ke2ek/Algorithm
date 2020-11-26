// https://algospot.com/judge/problem/read/MATCHFIX
#include <iostream>
#include <vector>
#include <queue>
#define INF 987654321
using namespace std;

int N, M, V;
vector<vector<int> > capacity;
vector<vector<int> > flow;
vector<int> wins;
int totalFlow;

void makeNetwork() {
    V = N + M + 2;
    capacity = vector<vector<int> > (V, vector<int> (V, 0));
    flow = vector<vector<int> > (V, vector<int> (V, 0));
    // Index of Node
    //  0 = src
    //  1 ~ M = match
    //  (M + 1) ~ (M + N) = players
    //  N + M + 1 = sink
    for (int m = 1; m <= M; m++) {
        int player1, player2;
        cin >> player1 >> player2;
        // source-to-matching
        capacity[0][m] = 1;
        // matching-to-player
        capacity[m][M + player1 + 1] = 1;
        capacity[m][M + player2 + 1] = 1;
    }
    
    // Initialize
    totalFlow = 0;
}

void networkFlow(int source, int sink) {
    //int totalFlow = 0;
    while (true) {
        vector<int> parent(V, -1);
        queue<int> q;
        parent[source] = source;
        q.push(source);
        while (!q.empty() && parent[sink] == -1) {
            int u = q.front();
            q.pop();
            for (int v = 0; v < V; v++) {
                //cout << "capacity[" << u << "][" << v << "] = " << capacity[u][v] << endl;
                //cout << "flow[" << u << "][" << v << "] = " << flow[u][v] << endl;
                if ((capacity[u][v] - flow[u][v]) > 0 && parent[v] == -1) {
                    q.push(v);
                    parent[v] = u;
                }
            }
        }
        if (parent[sink] == -1) break;
        int amount = INF;
        for (int v = sink; v != source; v = parent[v]) {
            int residual = capacity[parent[v]][v] - flow[parent[v]][v];
            if (residual < amount)
                amount = residual;
        }
        for (int v = sink; v != source; v = parent[v]) {
            flow[parent[v]][v] += amount;
            flow[v][parent[v]] -= amount;
        }
        totalFlow += amount;
    }
}

bool exceed(int W) {
    for (int player = 1; player < N; player++)
        if (wins[player] + flow[M + player + 1][V - 1] >= W)
            return true;
    return false;
}

bool canWin(int W) {
    if (exceed(W)) return false;
    
    // Update capacity on player-to-sink
    for (int player = 0; player < N; player++) {
        int maxWins = (player == 0) ? W : W - 1;
        capacity[M + player + 1][V - 1] = maxWins - wins[player];
    }
    
    networkFlow(0, V - 1);
    return totalFlow == M;
}

// O(M^2)
void solve() {
    cin >> N >> M;
    wins = vector<int> (N);
    for (int i = 0; i< N; i++) cin >> wins[i];
    
    makeNetwork();
    int minRequiredWins = -1;
    for (int W = wins[0]; W <= wins[0] + M; W++) {
        if (canWin(W)) {
            minRequiredWins = W;
            break;
        }
    }
    
    if (exceed(wins[0] + flow[M + 1][V - 1]))
        minRequiredWins = -1;
    
    cout << minRequiredWins << endl;
}

int main() {
    int tc;
    cin >> tc;
    while(tc--)
        solve();
    return 0;
}
