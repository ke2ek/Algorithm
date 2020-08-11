// https://algospot.com/judge/problem/read/FAMILYTREE
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = numeric_limits<int>::max();

struct RMQ {
    int n;
    vector<int> rangeMin; // the minimum value of each range.
    
    RMQ(const vector<int>& array) {
        n = array.size();
        rangeMin.resize(4*n);
        init(array, 0, n-1, 1);
    }
    
    // O(n)
    int init(const vector<int>& array, int left, int right, int node) {
        if (left == right)
            return rangeMin[node] = array[left];
        int mid = (left + right) / 2;
        int leftMin = init(array, left, mid, node * 2);
        int rightMin = init(array, mid + 1, right, node * 2 + 1);
        return rangeMin[node] = min(leftMin, rightMin);
    }
    
    // O(lg(n))
    int query(int left, int right, int node, int nodeLeft, int nodeRight) {
        if (right < nodeLeft || nodeRight < left)
            return MAX;
        if (left <= nodeLeft && nodeRight <= right)
            return rangeMin[node];
        int mid = (nodeLeft + nodeRight) / 2;
        return min(query(left, right, node * 2, nodeLeft, mid),
                   query(left, right, node * 2 + 1, mid + 1, nodeRight));
    }
    
    // External Interface
    int query(int left, int right) {
        return query(left, right, 1, 0, n - 1);
    }
};

const int MAX_N = 100000;
int n;
vector<int> child[MAX_N];
int no2serial[MAX_N], serial2no[MAX_N]; // array for conversion
int locInTrip[MAX_N]; // the first location of each node
int depth[MAX_N]; // the depth of each node
int nextSerial; // the next serial number (!= the index of node)

void traverse(int here, int d, vector<int>& trip) {
    no2serial[here] = nextSerial;
    serial2no[nextSerial] = here;
    ++nextSerial;
    
    // calc depth
    depth[here] = d;
    
    // add serial number to trip
    locInTrip[here] = trip.size(); // visiting order
    trip.push_back((no2serial[here]));
    
    // visit children
    for (int i=0; i<child[here].size(); i++) {
        traverse(child[here][i], d+1, trip);
        // check the case coming back to current node for visiting order
        trip.push_back(no2serial[here]);
    }
}

// O(n)
// Generate RMQ Segment Tree
RMQ* prepareRMQ() {
    nextSerial = 0;
    vector<int> trip; // trip[i] = Number of the i-th visited node
    traverse(0, 0, trip);
    // trip has the sequence when visited
    return new RMQ(trip);
}

// O(lg(n))
// Return distance between u and v
int distance(RMQ* rmq, int u, int v) {
    // find the first location
    int lu = locInTrip[u], lv = locInTrip[v];
    if (lu > lv) swap(lu, lv);
    // query() returns node number of Least Common Ancestor(LCA) of both u and v
    int lca = serial2no[rmq->query(lu, lv)];
    return depth[u] + depth[v] - 2 * depth[lca];
}

void solve() {
    for (int i=0; i<n; i++) {
        child[i].clear();
    }
    
    int q;
    scanf("%d %d", &n, &q);
    for (int i=1; i<n; i++) {
        int parent;
        scanf("%d", &parent);
        child[parent].push_back(i);
    }
    RMQ* rmq = prepareRMQ();
    for (int i=0; i<q; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        printf("%d\n", distance(rmq, a, b));
    }
    delete rmq;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}
