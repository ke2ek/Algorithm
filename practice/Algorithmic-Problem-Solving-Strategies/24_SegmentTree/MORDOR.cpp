// https://algospot.com/judge/problem/read/MORDOR
#include <cstdio>
#include <vector>

#define max(x, y) (x < y) ? y : x
#define min(x, y) (x < y) ? x : y
using namespace std;
typedef pair<int, int> pii;

class SegmentTree {
private:
    int n;
    vector<pii > rangeData; // the maximum, minimum value of each range.

public:
    SegmentTree(const vector<int>& array)
    {
        n = array.size();
        rangeData.resize(4*n);
        init(array, 0, n-1, 1);
    }
    
    // O(n)
    pii init(const vector<int>& array,
             int left, int right, int node)
    {
        if (left == right) {
            return rangeData[node] = pii (array[left], array[left]);
        }
        
        int mid = (left + right) / 2;
        pii leftPair = init(array, left, mid, node * 2);
        pii rightPair = init(array, mid + 1, right, node * 2 + 1);
        pii ret(max(leftPair.first, rightPair.first),
                           min(leftPair.second, rightPair.second));
        return rangeData[node] = ret;
    }
    
    // Q(lg(n))
    pii query(int left, int right, int node,
                         int nodeLeft, int nodeRight)
    {
        if (nodeRight < left || nodeLeft > right)
            return pair<int,int> (-1, 20001);
        
        if (nodeLeft >= left && nodeRight <= right)
            return rangeData[node];
        
        int mid = (nodeLeft + nodeRight) / 2;
        pii leftPair = query(left, right, node * 2, nodeLeft, mid);
        pii rightPair = query(left, right, node * 2 + 1, mid + 1, nodeRight);
        pii ret(max(leftPair.first, rightPair.first),
                           min(leftPair.second, rightPair.second));
        return ret;
    }
    
    pii query(int left, int right) {
        return query(left, right, 1, 0, n-1);
    }
};

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, q;
        scanf("%d %d", &n, &q);
        vector<int> arr(n);
        for (int i=0; i<n; i++) scanf("%d", &arr[i]);
        SegmentTree *tree = new SegmentTree(arr);
        for (int i=0; i<q; i++) {
            int a, b;
            scanf("%d %d", &a, &b);
            pii result = tree->query(a, b);
            printf("%d\n", (result.first - result.second));
        }
        
    }
    return 0;
}
