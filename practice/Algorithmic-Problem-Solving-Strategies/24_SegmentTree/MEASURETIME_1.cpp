// https://algospot.com/judge/problem/read/MEASURETIME#
#include <cstdio>
#include <vector>
using namespace std;

class FenwickTree {
private:
    vector<int> tree;
    
public:
    FenwickTree(int n) {
        tree.resize(n+1, 0);
    }
    
    // return the partial sum of [0, pos].
    int psum(int pos) {
        pos++;
        int ret = 0;
        // the index starts at 1
        while (pos > 0) {
            ret += tree[pos];
            pos &= (pos - 1);
        }
        return ret;
    }
    
    // for update, a new value is added or subtracted at the desired position.
    void add(int pos, int val) {
        pos++;
        while (pos < tree.size()) {
            tree[pos] += val;
            pos += pos & -pos;
        }
    }
};

long long countMoves(const vector<int> &A) {
    FenwickTree tree(1000000);
    long long ret = 0;
    for (int i=0; i<A.size(); i++) {
        // get the count of numbers larger than A[i].
        ret += tree.psum(999999) - tree.psum(A[i]);
        // save the frequency of each number.
        tree.add(A[i], 1);
    }
    return ret;
}

void solve() {
    int n;
    scanf("%d", &n);
    vector<int> A(n);
    for (int i=0; i<n; i++) scanf("%d", &A[i]);
    printf("%lld\n", countMoves(A)); // Using Fenwick Tree
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}
