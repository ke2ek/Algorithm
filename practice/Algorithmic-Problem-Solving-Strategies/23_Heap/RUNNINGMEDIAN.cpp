// https://algospot.com/judge/problem/read/RUNNINGMEDIAN
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

struct RNG {
    int seed, a, b;
    RNG(int _a, int _b) : a(_a), b(_b), seed(1983) {}
    int next() {
        int ret = seed;
        // Notice that (long long) type casting is used to avoid integer overflow.
        seed = ((seed * (long long)a) + b) % 20090711;
        return ret;
    }
};

/*
 * Key Idea: Saving separately left-half and right-half of the nodes ordered by ascending.
 * 1. the size of max-heap is equal or one more than the size of min-heap.
 * 2. the maximum element of max-heap is equal or lesser than the minimum element of min-heap.
 * (root of max-heap <= root of min-heap)
 */
int runningMedian(int n, RNG rng) { // O(N*lgN)
    priority_queue<int, vector<int>, less<int> > maxHeap;
    priority_queue<int, vector<int>, greater<int> > minHeap;
    int ret = 0;
    for (int cnt = 1; cnt <= n; cnt++) {
        if (maxHeap.size() == minHeap.size())
            maxHeap.push(rng.next());
        else
            minHeap.push(rng.next());
        
        /* if the condition #2 is not kept, exchange each root. */
        if (!minHeap.empty() && !maxHeap.empty() &&
            minHeap.top() < maxHeap.top()) {
            int a = maxHeap.top(), b = minHeap.top();
            maxHeap.pop();
            minHeap.pop();
            maxHeap.push(b);
            minHeap.push(a);
        }
        ret = (ret + maxHeap.top()) % 20090711;
    }
    return ret;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n, a, b;
        cin >> n >> a >> b;
        cout << runningMedian(n, RNG(a, b)) << endl;
    }
    return 0;
}
