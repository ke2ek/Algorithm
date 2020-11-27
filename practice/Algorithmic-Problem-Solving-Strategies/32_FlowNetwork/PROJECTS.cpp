#include <iostream>
#include <vector>
#include <queue>
#define INF 987654321
using namespace std;

int N, M, V;
int revenueSum;
vector<vector<int> > capacity;
vector<vector<int> > flow;

void makeNetwork() {
    cin >> N >> M;
    // Index of Nodes
    //  0: S
    //  1 ~ N: business
    //  (N + 1) ~ (N + M): equipment
    //  N + M + 1: T
    V = N + M + 2;
    capacity = vector<vector<int> > (V, vector<int> (V, 0));
    flow = vector<vector<int> > (V, vector<int> (V, 0));
    revenueSum = 0;
    for (int n = 1; n <= N; n++) {
        // source-to-business
        cin >> capacity[0][n];
        revenueSum += capacity[0][n];
    }
    
    for (int m = 1; m <= M; m++) {
        // equipment-to-sink
        cin >> capacity[N + m][V - 1];
    }
    
    // business-to-equipment
    for (int n = 1; n <= N; n++) {
        for (int m = 1; m <= M; m++) {
            cin >> capacity[n][N + m];
            if (capacity[n][N + m] == 1)
                capacity[n][N + m] = INF;
        }
    }
}


int networkFlow(int source, int sink) {
    int totalFlow = 0;
    while (true) {
        vector<int> parent(V, -1);
        queue<int> q;
        parent[source] = source;
        q.push(source);
        while (!q.empty() && parent[sink] == -1) {
            int u = q.front();
            q.pop();
            for (int v = 0; v < V; v++) {
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
            if (amount > residual)
                amount = residual;
        }
        
        for (int v = sink; v != source; v = parent[v]) {
            flow[parent[v]][v] += amount;
            flow[v][parent[v]] -= amount;
        }
        totalFlow += amount;
    }
    return totalFlow;
}

void solve() {
    /* Calculate the maximum profit.
     *      max(profit) = sum(expected revenue) - the minimum capacity of Cut S, T
     *
     * Network Capacity:
     *  "source" -- expected revenue --> "business" -- INF --> "equipment" -- price --> "sink"
     *
     * There can be duplicate equipments used in different business, (But only one equipment is purchased.)
     * so the capacity of business-to-equipment layer is always INF.
     * If one of the selected businesses (in the set S) needs equipments in the set T,
     * its capacity (of Cut S, T) becomes always INF. (these cases are exception)
     *
     * The capacity of Cut S, T is defined as "sum(unselected business profits) + sum(selected equipment costs)"
     */
    makeNetwork();
    cout << revenueSum - networkFlow(0, V - 1) << endl;
    /* Test Case
     * Input:
        2
        2 2
        10 10
        5 10
        1 0
        1 1
        5 5
        260 60 140 350 500
        250 100 150 300 100
        1 0 0 0 0
        1 1 1 0 0
        0 0 1 1 0
        0 0 0 1 0
        0 0 0 1 1
     * Output:
        5
        460
     */
}

int main() {
    int tc;
    cin >> tc;
    while (tc--)
        solve();
    return 0;
}

